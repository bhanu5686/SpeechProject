// HMM.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

int qstar[O];
ld delta[O][N];
int phi[O][N];
ld alpha[O][N];
ld beta[O][N];
ld zeta[O][N][N];
ld Gamma[O][N];
ld pstar = 0.0;
int *obs;
int T;

ld raisedSineWeight[12] = {0.0};
ld tokhuraWeight[12] = {1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};
ld PI =  3.141592653589793238;
int digit[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};

double samples[100000];
ld stableSamples[framesize];
ld RIS[13] = {0.0};
ld AIS[13] = {0.0};
ld CIS[13] = {0.0};

int framecount;
ld CepsArray[1000][13];
ld CodeArray[32][13];

model lamda;
model lamda_new;
model lamda_temp;


void intialize_model()
{
    for (int i = 0; i < N; i++)
        if (i == 0)
            lamda.pi[i] = 1.0;
        else
            lamda.pi[i] = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i == j && i != N - 1)
                lamda.a[i][j] = 0.8;
            else if (i == j && i == N - 1)
                lamda.a[i][j] = 1;
            else if (j == i + 1)
                lamda.a[i][j] = 0.2;
            else
                lamda.a[i][j] = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            lamda.b[i][j] = 1.0 / M;
}

void clean_model()
{
    for (int i = 0; i < N; i++)
            lamda.pi[i] = 0.0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
                lamda.a[i][j] = 0.0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            lamda.b[i][j] = 0.0;
}

void clean_model_new()
{
    for (int i = 0; i < N; i++)
            lamda_new.pi[i] = 0.0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
                lamda_new.a[i][j] = 0.0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            lamda_new.b[i][j] = 0.0;
}


void printObs(int *x,int row)
{
    int i = 0;
    for (i = 0; i < row; i++)
    {
        printf("%d ",x[i]);
    }
    printf("\n");
}


void state_sequence()
{
    printf("\n\nobserved state sequence: \n\n");
    for(int t=0;t<T;t++)
    {
        printf("%d ",qstar[t]);
    }
}

bool writeFile(const char  *fileName)
{
	errno_t err;
    FILE *fp;
	err  = fopen_s( &fp, fileName, "w" );
    if( err != 0 )
        return false;
    else
    {
        fprintf(fp,"\nObservation Sequence :");
        fprintf(fp,"\nTotal iterations :");
        fprintf(fp,"\nFinal Probability of state sequence is:");
        fprintf(fp,"\nState Sequence :");
        fprintf(fp,"\nInitial State :");
        for(int i=0;i < N;i++) 
            fprintf(fp,"%Le ",lamda.pi[i]);
        fprintf(fp,"\nA Matrix :\n");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                fprintf(fp,"%Le ",lamda.a[i][j]);
            }
            fprintf(fp,"\n");
        }

        fprintf(fp,"\nB Matrix :\n");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                fprintf(fp,"%Le ",lamda.b[i][j]);
            }
            fprintf(fp,"\n");
        }
        
    }
    fclose(fp);
	return true;
}

ld viterbi()
{     
    int argmax = 0;
    for (int i = 0; i < T; i++)
        qstar[i] = 0;

    for (int i = 0; i < N; i++) //initialisation
    {
        delta[0][i] = ((lamda.pi[i]) * (lamda.b[i][obs[0]]));
        phi[0][i] = -1;
    }

    for (int t = 1; t < T; t++) //recursion
    {
        for (int j = 0; j < N; j++)
        {
            argmax = 0;
            for (int i = 1; i < N; i++)
            {
                if (delta[t - 1][i]*lamda.a[i][j] > delta[t - 1][argmax]*lamda.a[argmax][j])
                    argmax = i;
            }
            delta[t][j] = delta[t - 1][argmax] * lamda.a[argmax][j] * lamda.b[j][obs[t]];
            phi[t][j] = argmax;
        }
    }
    argmax = 0;
    for (int i = 1; i < N; i++) //termination
    {
        if (delta[T - 1][i] > delta[T - 1][argmax])
            argmax = i;
    }

    pstar = delta[T - 1][argmax];
    qstar[T - 1] = argmax;

    for (int t = T - 2; t >= 0; t--) //backtracking
    {
        qstar[t] = phi[t + 1][qstar[t + 1]];
    }
    //printObs(qstar,T);
    //printf("%Le ", pstar);
    return pstar;
}

ld forward_algo()
{    
    ld sum = 0.0;

    for (int j = 0; j < N; j++) //initialisation
    {
        alpha[0][j] = lamda.pi[j] * lamda.b[j][obs[0]];        
    }

    for (int t = 1; t < T; t++) //recursion
    {
        for (int j = 0; j < N; j++)
        {            
            sum = 0.0;
            for (int i = 0; i < N; i++)
            {
                sum += alpha[t-1][i] * lamda.a[i][j] * lamda.b[j][obs[t]];
            }
            alpha[t][j] = sum;
        }
    }

    sum = 0.0;
    for (int i = 0; i < N; i++) //termination
    {
        sum += alpha[T-1][i];
    }

    //printf("%Le ", sum);
    return sum;
}

ld backward_algo()
{
    
    ld sum = 0.0;

    for (int j = 0; j < N; j++) //initialisation
    {
        beta[T-1][j] = 1;
    }

    for (int t = T-2; t >= 0; t--) //recursion
    {
        for (int j = 0; j < N; j++)
        {            
            sum = 0.0;
            for (int i = 0; i < N; i++)
            {
                sum += lamda.a[j][i] * lamda.b[i][obs[t+1]] * beta[t+1][i];
            }
            beta[t][j] = sum;
        }
    }

    sum = 0.0;
    for (int j = 0; j < N; j++) //termination
    {
        sum += beta[0][j];
    }

    //printf("%Le ", sum);
    return sum;
}

void Gamma_cal()
{
    ld sum = 0.0;
    int argmax = 0;
    int q[O];
    for (int t = 0; t < T; t++)
    {
        for (int i = 0; i < N; i++)
        {
            ld value = alpha[t][i] * beta[t][i];
            sum = 0.0;
            for (int j = 0; j < N; j++)
            {
                sum += alpha[t][j] * beta[t][j];
            }
            Gamma[t][i] = value/sum;
            if(Gamma[t][i] > Gamma[t][argmax])
                argmax = i;
        }
        q[t] = argmax;
    }
}

void zeta_cal()
{
    ld sum = 0.0;
    for (int t = 0; t < T-1; t++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {

                ld value = alpha[t][i] * lamda.a[i][j] * lamda.b[j][obs[t+1]] * beta[t+1][j];
                sum = 0.0;
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        sum += alpha[t][i] * lamda.a[i][j] * lamda.b[j][obs[t+1]] * beta[t+1][j];
                    }
                }
                zeta[t][i][j] = value/sum;           
            }            
        }
    }
}

void Baum_Welch_reestimation()
{
    ld value, sum; 
    for (int i = 0; i < N; i++) 
        lamda.pi[i] = Gamma[0][i];
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++)
        {
            value = 0;
            sum = 0;
            for (int t = 0; t < T - 2; t++)
            {
                value += zeta[t][i][j];
                sum += Gamma[t][i];
            }
            lamda.a[i][j] = value / sum;
        }
    }
    for (int j = 0; j < N; j++) 
    {
        for (int k = 0; k < M; k++)
        {
            value = 0;
            sum = 0;
            for (int t = 0; t < T; t++)
            {
                if (obs[t] == k)
                    value += Gamma[t][j];
            }
            for (int t = 0; t < T - 1; t++)
            {
                sum += Gamma[t][j];
            }
            lamda.b[j][k] = value / sum;
        }
    }
}

model getAverageModel(int cnt)
{
    for (int i = 0; i < N; i++)
        lamda.pi[i] = lamda_new.pi[i]/cnt;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            lamda.a[i][j] = lamda_new.a[i][j]/cnt;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            lamda.b[i][j] = lamda_new.b[i][j]/cnt;
	return lamda;
}

void modify_BMatrix()
{    
      for(int i=0;i<N;i++)
    {
        int count=0;
        int max=-1;
        int maxindex=-1;
        int sum=0;
        
        for(int j=0;j<M;j++)
        {
            if(max<lamda.b[i][j])
            {
                max=lamda.b[i][j];
                maxindex=j;
            }
            if(lamda.b[i][j]<pow(10.0,-30))
            {
                count++;
                sum+=lamda.b[i][j];
                lamda.b[i][j]=pow(10.0,-30);
            }   
        }
        lamda.b[i][maxindex]-=count*pow(10.0,-30)+sum;
    }
}

void modify_model()
{
    ld maxx=0.0,sum=0.0;
    int cnt=0,index=0;

    for (int i = 0; i < N; i++)
    {
        maxx = lamda_temp.a[i][0];cnt=0;sum=0.0;index=0;
        for (int j = 0; j < N; j++)
        {
            sum += lamda_temp.a[i][j];
            if(lamda_temp.a[i][j] > maxx)
            {
                maxx = lamda_temp.a[i][j];
                index = j;
            }
        }
        if(sum > 1)
        {
            ld miss_value = sum - 1;
            lamda_temp.a[i][index] -= miss_value; 
        }
        else if(sum < 1)
        {
            ld miss_value = 1 - sum;
            lamda_temp.a[i][index] += miss_value; 
        }
    }


    for (int i = 0; i < N; i++)
    {
        maxx = lamda_temp.b[i][0];sum=0.0;index=0;
        for (int j = 0; j < M; j++)
        {
            sum += lamda_temp.b[i][j];
            if(lamda_temp.b[i][j] > maxx)
            {
                maxx = lamda_temp.b[i][j];
                index = j;
            }
        }
        if(sum > 1)
        {
            ld miss_value = sum - 1;
            lamda_temp.b[i][index] -= miss_value; 
        }
        else if(sum < 1)
        {
            ld miss_value = 1 - sum;
            lamda_temp.b[i][index] += miss_value; 
        }
    }
}

bool ReadFile(double *samples, const char  *fileName)
{
	errno_t err;
    FILE *fp;
	err  = fopen_s( &fp, fileName, "r" );
    if( err != 0 )
        return false;
    else
    {
        int i = 5, a;
        char buffer[100];
        while (i--)
        {
            fgets(buffer, 100, fp);
        }
        i = 0;
        while (fscanf_s(fp, "%d", &a) != EOF)
        {
            samples[i++] = (double)a;
        }
    }
    fclose(fp);
    return true;
}

void DCShift(double *samples, int size)
{
    int i = 0;
    double sum = 0;
    for (i = 0; i < size; i++)
    {
        sum = sum + samples[i];
    }
    sum = sum / size ;
    for (i = 0; i < size; i++)
    {
        samples[i] = samples[i] - sum ;
    }
    return;
}

void Normalization(double *samples, int size)
{

    double maxx = 0.0;
    int i = 0;

    for (; i < size; i++)
    {
        if (maxx < samples[i])
            maxx = samples[i];
    }

    for (int i = 0; i < size; i++)
    {
        samples[i] /= maxx;
        samples[i] *= 5000;
    }
    return;
}

int sizeOfFile(const char  *fileName)
{
	errno_t err;
    FILE *fp;
    int cnt = 0;    
	err  = fopen_s( &fp, fileName, "r" );
    if( err != 0 )
        return -1;
    else
    {
        int i = 5, a;
        char buffer[100];
        while (i--)
        {
            fgets(buffer, 100, fp);
        }
        while (fscanf_s(fp, "%d", &a) != EOF)
        {
            cnt++;
        }
    }
    fclose(fp);
    return cnt;
}

void ComputeRIS()
{
    int i, j, x = 320;
    ld n = (ld)x;
    for (i = 0; i <= 12; i++)
    {
        ld sum = 0.0;
        for (j = 0; j < framesize - i; j++)
        {
            sum = sum + (stableSamples[j] * stableSamples[i + j]);
        }
        sum = sum / n;

        RIS[i] = sum;
    }
    return;
}

void ComputeAIS()
{
    ld energy[13] = {0.0};
    ld K[13] = {0.0};
    ld newAlpha[13] = {0.0};
    ld prevAlpha[13] = {0.0};

    energy[0] = RIS[0];

    int i = 0, j = 0;

    for (i = 1; i <= 12; i++)
    {
        if (i == 1)
            K[i] = RIS[i] / RIS[0];
        else
        {
            ld sum = 0.0;
            for (j = 1; j < i; j++)
            {
                prevAlpha[j] = newAlpha[j];
                sum += (prevAlpha[j] * RIS[i - j]);
            }
            K[i] = (RIS[i] - sum) / energy[i - 1];
        }

        newAlpha[i] = K[i];
        for (j = 1; j < i; j++)
        {
            newAlpha[j] = prevAlpha[j] - (K[i] * prevAlpha[i - j]);
        }
        energy[i] = (1 - (K[i] * K[i])) * energy[i - 1];
    }
    for (i = 1; i <= 12; i++)
        AIS[i] = newAlpha[i];
    return;
}

void ComputeCIS()
{
    CIS[0] = logl(RIS[0]);

    int m = 0, k = 0;
    for (m = 1; m <= 12; m++)
    {
        ld sum = 0.0;

        for (k = 1; k < m; k++)
        {
            sum += ((((ld)k) * CIS[k] * AIS[m - k]) / ((ld)m));
        }

        ld value = AIS[m] + sum;
        CIS[m] = value;
    }
    return;
}

void RiasedSineWindow()
{
    for (int i = 1; i <= 12; i++)
    {
        CIS[i] = raisedSineWeight[i - 1] * CIS[i];
    }
    return;
}

void ComputeRSW()
{
    for (int i = 1; i <= 12; i++)
    {
        ld m = (ld)i;
        ld theta = (PI * m) / 12.0;
        ld value = sin(theta);
        value = 1.0 + (6.0 * value);
        raisedSineWeight[i - 1] = value;
    }
    return;
}

ld tokhura(ld *x,ld *y)
{
    ld dist = 0.0;
    for(int i=0;i<12;i++)
    {
        dist += (tokhuraWeight[i] * (x[i]-y[i]) * (x[i]-y[i])); 
    }
    ld value = dist/12.0;
    return value;
}

void getObsSeq()
{
    int i = 0, j = 0, index = 0;
    ld minDist = 0.0, tDist = 0.0;
    for (i = 0; i < T; i++)
    {
        minDist = tokhura(CepsArray[i], CodeArray[0]);
        for (j = 1; j < 32; j++)
        {
            tDist = tokhura(CepsArray[i], CodeArray[j]);
            if (tDist < minDist)
            {
                minDist = tDist;
                index = j;
            }
        }
        obs[i] = index;
    }
}

void readCodeBook()
{
	errno_t err;
    FILE *fp;    
	err  = fopen_s( &fp, "Codebook.txt", "r" );
    if( err != 0 )
    {
        printf("unable to open codebook file\n");
        return;
    }
    else
    {
        char buffer[200];
        ld val = 0.0;
        int i = 0, j = 0;		
        while (fgets(buffer, 200, fp))
        {
            j = 0;
			char *next_token = NULL;
            char* token = strtok_s(buffer, " ",&next_token);
            while (token != NULL)
            {
                val = strtod(token, NULL);
                CodeArray[i][j++] = val;
                token = strtok_s(NULL, " ",&next_token);
            }
            i++;
        }
    }
    fclose(fp);
    return;
}

bool obsGenerate(const char  *filename)
{
    T = 0;
    int row = sizeOfFile(filename);
    if (row == -1)
    {
        printf("unable to open file");
        return false;
    }
    //printf("Working on %s\n",filename);
    //printf("\nsize of file :%d\n",row);
    if (!ReadFile(samples, filename))
    {
        printf("\nunable to open input_files!..");
        return false;
    }
    DCShift(samples, row);
    Normalization(samples, row);
    framecount = row / framesize;

    T=0;
    
    for (int i = 0, k = 0; k <= (240 * 160) && k < row - 240; i++, k += 240)
    {
        T++;

        for (int j = 0; j < 320; j++)
            stableSamples[j] = (ld)samples[j + k];

        for(int j=0;j<13;j++)
        {
            RIS[j] = 0.0;
            AIS[j] = 0.0;
            CIS[j] = 0.0;
        }

        ComputeRIS();
        ComputeAIS();
        ComputeCIS();
        RiasedSineWindow();

        for(int j=0;j<13;j++)
            CepsArray[i][j] = CIS[j];
    }
    obs = new int[T];
    getObsSeq();
    return true;
}

bool writeModel(const char  *fileName)
{
	errno_t err;
    FILE *fp;    
	err  = fopen_s( &fp, fileName, "w" );
    if( err != 0 )
    {
        return false;
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            fprintf(fp, "%Le ", lamda.pi[i]);
        }
        fprintf(fp, "\n\n");

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                fprintf(fp, "%Le ", lamda.a[i][j]);
            }
            fprintf(fp, "\n");
        }
        fprintf(fp, "\n");

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                fprintf(fp, "%Le ", lamda.b[i][j]);
            }
            fprintf(fp, "\n");
        }
		printf("Model %s generated\n",fileName);
    }
    fclose(fp);
    return true;
}

bool ReadModel(const char  *fileName)
{
    errno_t err;
    FILE *fp;    
	err  = fopen_s( &fp, fileName, "r" );
    if( err != 0 )
        return false;
    else
    {
        char buffer[2000];
        ld val = 0.0;
        int i = 0, j = 0,k=0;
        while (fgets(buffer, 2000, fp))
        {
            k++;
            if(k == 1)
            {
                j=0;
				char *next_token = NULL;
                char* token = strtok_s(buffer, " ",&next_token);
                while (token != NULL)
                {
                    val = strtod(token, NULL);
                    lamda.pi[j++] = val;
                    token = strtok_s(NULL, " ",&next_token);
                }
            }
            else if(k >= 3 && k <= 7)
            {        
                j=0;
				char *next_token = NULL;
                char* token = strtok_s(buffer, " ",&next_token);
                while (token != NULL)
                {
                    val = strtod(token, NULL);
                    lamda.a[i][j++] = val;
                    token = strtok_s(NULL, " ",&next_token);
                }
                i++;
            }
            else if(k >= 9 && k <= 13)
            {
                j=0;
                if (k == 9)
                    i = 0;
				char *next_token = NULL;
                char* token = strtok_s(buffer, " ",&next_token);
                while (token != NULL)
                {
                    val = strtod(token, NULL);
                    lamda.b[i][j++] = val;
                    token = strtok_s(NULL, " ",&next_token);
                }
                i++;
            }
        }
    }
    fclose(fp);
    return true; 
}

void ModelAverage()
{
    for (int i = 0; i < N; i++)
        lamda_new.pi[i] += lamda.pi[i];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            lamda_new.a[i][j] += lamda.a[i][j];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            lamda_new.b[i][j] += lamda.b[i][j];
}

void hmm_training()
{
    int i = 0, j = 0, k = 0;
    printf("\nTraining of hmm model starts..\n\n");
    for (i = 0; i < 10; i++)
    {
        int count = 5, k = 0;
        clean_model();
        while (count--)
        {
            clean_model_new();
            //printf("\nCount of iteration : %d\n",count + 1);
            k = 0;
            for (j = 1; j <= 20; j++)
            {
                T = 0;
				char filename[160];
				sprintf_s(filename,"input_files/%d_%d.txt",i,j);
                if (!obsGenerate(filename))
                    continue;
                if (count == 4)
                    intialize_model();
				else
					lamda = lamda_temp;
                int iteration = 25;
                while (iteration--)
                {
                    forward_algo();
                    backward_algo();
                    Gamma_cal();
                    viterbi();
                    zeta_cal();
                    Baum_Welch_reestimation();
                    modify_BMatrix();
                }
                modify_BMatrix();
                ModelAverage();
                delete[] obs;
            }
            lamda_temp = getAverageModel(20);
            modify_model();
        }
		char fileName[160];
		sprintf_s(fileName,"Model/%d.txt",i);
        writeModel(fileName);
    }
}

void hmm_testing()
{
    int accuracy = 0, total = 0;
    int i = 0, j = 0, k = 0;
    printf("\nTesting of hmm model starts..\n\n");
    for (i = 2; i < 3; i++)
    {
        k = 0;
        for (j = 1; j <= 10 ; j++)
        {
            total++;
            T=0;
			char filename[160];
			sprintf_s(filename,"input_files/%d_%d.txt",i,j);
            if (!obsGenerate(filename))
                continue;
            //printObs(obs, T);
            ld maxx = 0.0;
            int index = -1;
            for (int k = 0; k < 10; k++)
            {
				char filename[160];
				sprintf_s(filename,"Model/%d.txt",k);
                clean_model();
                ReadModel(filename);
                ld value = forward_algo();
                printf("\nForward Probability for %d : %Le", digit[k], value);
                if (value > maxx)
                {
                    maxx = value;
                    index = k;
                }
            }
            if (index != -1)
			{
				if (digit[index] == 10)
					printf("\nDigit identified : %s\n\n","plus");
				else if (digit[index] == 11)
					printf("\nDigit identified : %s\n\n","minus");
				else if (digit[index] == 12)
					printf("\nDigit identified : %s\n\n","star");
				else if (digit[index] == 13)
					printf("\nDigit identified : %s\n\n","divide");
				else 
					printf("\nDigit identified : %d\n\n",digit[index]);
			}
            else
                printf("\nnot recognized\n\n");
            if (digit[index] == i)
                accuracy++;
            delete[] obs;
        }
    }
    printf("Accuracy : %Lf %", ((ld)accuracy / (ld)total) * 100);
}

int liveTesting()             
{
    system("Recording\\Recording_Module.exe 2 input_file.wav input_file.txt");

	char filename[160];
	sprintf_s(filename,"input_file.txt");

    T = 0;
    if (!obsGenerate(filename))
    {
        printf("unable to test file ");
    }
    ld maxx = 0.0;
    int index = -1;
    for (int k = 0; k < 10; k++)
    {
		char filename[160];
		sprintf_s(filename,"Model/%d.txt",k);
        clean_model();
        ReadModel(filename);
        ld value = forward_algo();
        //printf("\nForward Probability for %d : %Le", digit[k], value);
        if (value > maxx)
        {
            maxx = value;
            index = k;
        }
    }
	delete[] obs;
	return index;    
}

bool WriteRecording(const char  *fileName)
{
	errno_t err1,err2;
    FILE *fp,*wp;    
	char filename[160];
	sprintf_s(filename,"input_file.txt");
	err1  = fopen_s( &wp, filename, "r" );
	err2  = fopen_s( &fp, fileName, "w" );
    if( err1 != 0 )
    {
        return false;
    }
    else
    {
		int i = 5, a;
        char buffer[100];
        while (fscanf_s(wp, "%d", &a) != EOF)
        {
             fprintf(fp, "%d\n", a);
        }
    }
    fclose(fp);
	fclose(wp);
    return true;
}


void generaterecording()
{
	int i = 0, j = 0, k = 0;
    for (i = 10; i < 14; i++)
    {
		printf("\nEnter your choice : %d\n",i);
        k = 0;
        for (j = 1; j <= 20 ; j++)
        {
			system("Recording\\Recording_Module.exe 2 input_file.wav input_file.txt");
			char filename[160];
			sprintf_s(filename,"input_files/%d_%d.txt",i,j);
			WriteRecording(filename);            
        }
    }
}
