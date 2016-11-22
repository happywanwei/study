// ConvertIQ.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>

// Option values
#define OPT_IBIN        1
#define OPT_IWJ         2
#define OPT_IVSA        3
#define OPT_OBIN        4
#define OPT_OWJ         5
#define OPT_OVSA        6
#define OPT_OARR        7
#define OPT_OSAM        8
#define OPT_OUT         9

struct OptionList
{
    char *option;
    int value;
};

OptionList Options[] =
{
    {"-ibin", OPT_IBIN},
    {"-iwj",  OPT_IWJ},
    {"-ivsa", OPT_IVSA},
    {"-obin", OPT_OBIN},
    {"-owj",  OPT_OWJ},
    {"-ovsa", OPT_OVSA},
    {"-oarr", OPT_OARR},
    {"-osam", OPT_OSAM},
    {"-out", OPT_OUT},
    {NULL, 0},                  // End of the list
};

void Usage(void)
{
    printf("Usage: conviq <inputfile> <outputfile> [options]\n"
           "options:\n"
           "\t-ibin   Input file is binary\n"
           "\t-iwj    Input file is WaveJudge text\n"
           "\t-ivsa   Input file is VSA text\n"
           "\t-obin   Output file is binary\n"
           "\t-owj    Output file is WaveJudge text (S16, tab delimited)\n"
           "\t-ovsa   Output file is VSA text (fixed point, tab delimited)\n"
           "\t-oarr   Output file is C array (S16, comma delimited)\n"
           "Default is -ibin -ovsa\n");
}

char pNum[3];

void num2str(int value)
{
    pNum[0] = (value/100) + '0';
    value %= 100;
    pNum[1] = (value/10) + '0';
    value %= 10;
    pNum[2] = value + '0';
}

int main(int argc, char* argv[])
{
    char *inFile = NULL, *inFile2 = NULL, *outFile = NULL;
    char out_file[1000][20];
    char *pTTI = "UL_tti_";
    FILE *fin, *fin2, *fout;
    int inFmt = OPT_IBIN;
    int outFmt = OPT_OVSA;
    int tti_len = 1024*15;
    int i = 0;

    printf("Convert I/Q samples between different formats\n\n");
    if (argc > 1)
    {
        inFile = argv[1];
        printf("Input file name: %s\n", inFile);
    }
    if (argc > 5)
    {
        inFile2 = argv[2];
        printf("2nd Input file name: %s\n", inFile2);
        outFile = argv[3];
        printf("Output file name: %s\n", outFile);
    }
    else if (argc > 2)
    {
        outFile = argv[2];
        printf("Output file name: %s\n", outFile);
    }
    if (inFile == NULL || outFile == NULL)
    {
        Usage();
        return 1;
    }

    for(i=0; i<1000; i++)
    {
        memcpy(out_file[i], pTTI, 7);
        num2str(i);
        memcpy(&out_file[i][7], pNum, 3);
        memcpy(&out_file[i][10], ".txt", 4);
        out_file[i][15] = '\0';
    }

    // Look for option (can be in any order)
    if (argc > 5)
    {
        OptionList *iter = &Options[0];
        while (iter->option != NULL)
        {
            if (_stricmp(iter->option, argv[4]) == 0)
            {
                if (iter->value >= OPT_IBIN && iter->value <= OPT_IVSA)
                    inFmt = iter->value;
                else
                    outFmt = iter->value;
                break;
            }
            iter++;
        }
        // Something wrong was specified
        if (iter->option == NULL)
        {
            printf("Unknown option 3: %s\n", argv[4]);
            Usage();
            return 2;
        }
    }
    else if (argc > 4)
    {
        OptionList *iter = &Options[0];
        while (iter->option != NULL)
        {
            if (_stricmp(iter->option, argv[3]) == 0)
            {
                if (iter->value >= OPT_IBIN && iter->value <= OPT_IVSA)
                    inFmt = iter->value;
                else
                    outFmt = iter->value;
                break;
            }
            iter++;
        }
        // Something wrong was specified
        if (iter->option == NULL)
        {
            printf("Unknown option 3: %s\n", argv[4]);
            Usage();
            return 2;
        }
    }
    else if(argc > 3)
    {
        OptionList *iter = &Options[0];
        while (iter->option != NULL)
        {
            if (_stricmp(iter->option, argv[3]) == 0)
            {
                if (iter->value >= OPT_IBIN && iter->value <= OPT_IVSA)
                    inFmt = iter->value;
                else
                    outFmt = iter->value;
                break;
            }
            iter++;
        }
        // Something wrong was specified
        if (iter->option == NULL)
        {
            printf("Unknown option 3: %s\n", argv[3]);
            Usage();
            return 2;
        }
    }

    // Repeat same search for next option if exist
    if (argc > 5)
    {
        OptionList *iter = &Options[0];
        while (iter->option != NULL)
        {
            if (_stricmp(iter->option, argv[5]) == 0)
            {
                if (iter->value >= OPT_IBIN && iter->value <= OPT_IVSA)
                    inFmt = iter->value;
                else
                    outFmt = iter->value;
                break;
            }
            iter++;
        }
        // Something wrong was specified
        if (iter->option == NULL)
        {
            printf("Unknown option 4: %s\n", argv[5]);
            Usage();
            return 3;
        }
    }
    else if (argc > 4)
    {
        OptionList *iter = &Options[0];
        while (iter->option != NULL)
        {
            if (_stricmp(iter->option, argv[4]) == 0)
            {
                if (iter->value >= OPT_IBIN && iter->value <= OPT_IVSA)
                    inFmt = iter->value;
                else
                    outFmt = iter->value;
                break;
            }
            iter++;
        }
        // Something wrong was specified
        if (iter->option == NULL)
        {
            printf("Unknown option 4: %s\n", argv[4]);
            Usage();
            return 3;
        }
    }

    if(argc > 5)
    {
        if (inFmt == OPT_IBIN)
        {
            fopen_s(&fin, inFile, "rb");
            fopen_s(&fin2, inFile2, "rb");
        }
        else
        {
            fopen_s(&fin, inFile, "r");
            fopen_s(&fin2, inFile2, "r");
        }
        if (fin == NULL || fin2 == NULL)
        {
            printf("ERROR: Unable to open file '%s'\n", inFile);
            return 4;
        }
    }
    else
    {
        if (inFmt == OPT_IBIN)
        {
            fopen_s(&fin, inFile, "rb");
        }
        else
        {
            fopen_s(&fin, inFile, "r");
        }
        if (fin == NULL)
        {
            printf("ERROR: Unable to open file '%s'\n", inFile);
            return 4;
        }
    }
    if (outFmt == OPT_OBIN)
        fopen_s(&fout, outFile, "wb");
    else
        fopen_s(&fout, outFile, "w");
    if (fout == NULL)
    {
        printf("ERROR: Unable to open file '%s'\n", outFile);
        return 5;
    }

    if (outFmt == OPT_OVSA)
    {
        // Write header
        char fmt[] = "InputZoom\t%s\n"
                     "InputCenter\t%.1f\n"
                     "InputRange\t%.15f\n"
                     "InputRefImped\t%.1f\n"
                     "XStart\t%.1f\n"
                     "XDelta\t%.14G\n"
                     "XDomain\t%i\n"
                     "XUnit\t%s\n"
                     "YUnit\t%s\n"
                     "FreqValidMax\t%.1f\n"
                     "FreqValidMin\t%.1f\n"
                     "Y\n";
        fprintf(fout, fmt,
                "TRUE",
                2535000000.0,
                0.316227766016838,
                50.0,
                0.0,
                6.51041666666666E-08,
                2,
                "Sec",
                "V",
                2547000000.0,
                2523000000.0);
    }

    if (inFmt == OPT_IWJ)
    {
        double arg1 = 2048.0;
        int I, Q, uI, uQ;
        short i, q;

        printf("Input format: WaveJudge\n");
        while (!feof(fin))
        {
            fscanf_s(fin, "%i %i %i %i", &I, &Q, &uI, &uQ);
            if (outFmt == OPT_OVSA)
            {
                fprintf(fout, "%3.9f\t%3.9f\n", (double)I / arg1, (double)Q / arg1);
            }
            else if (outFmt == OPT_OBIN)
            {
                i = (short) I;
                q = (short) Q;
                fwrite(&i, sizeof(short), 1, fout);
                fwrite(&q, sizeof(short), 1, fout);
            }
            else if (outFmt == OPT_OARR)
            {
                fprintf(fout, "%i, %i,\n", I, Q);
            }
            else if(outFmt == OPT_OUT)
            {
                fprintf(fout, "%i %i\n", I, Q);
            }
        }
    }
    else if (inFmt == OPT_IVSA)
    {
        double arg1 = 2048.0;
        double I, Q;
        short i, q;

        printf("Input format: VSA\n");
        while (!feof(fin))
        {
            int converted = fscanf_s(fin, "%lf %lf\n", &I, &Q);
            if (converted != 2)
                continue;               // Skip header
            if (outFmt == OPT_OWJ)
            {
                fprintf(fout, "%i\t%i\n", (int) (I * arg1), (int) (Q * arg1));
            }
            else if (outFmt == OPT_OBIN)
            {
                i = (short) (I * arg1);
                q = (short) (Q * arg1);
                fwrite(&i, sizeof(short), 1, fout);
                fwrite(&q, sizeof(short), 1, fout);
            }
            else if (outFmt == OPT_OARR)
            {
                fprintf(fout, "%i, %i,\n", (int) (I * arg1), (int) (Q * arg1));
            }
        }
    }
    else if (inFmt == OPT_IBIN)
    {
        int j=0,k=0,l=0,sf=0,sym=0;
        printf("Input format: binary\n");
        if(outFmt == OPT_OSAM)
            fopen_s(&fout, out_file[0], "w");
        while (!feof(fin))
        {
            short buf[2];
            short buf2[2];
            double arg1 = 2048.0;
            
            if(outFmt == OPT_OSAM)
            {
                for(; l<312; l++)
                {
                    if(fout)
                    fprintf(fout, "%i %i\n", 0, 0);
                }
            }

            fread(buf, sizeof(short), 2, fin);
            //
            if (outFmt == OPT_OVSA)
            {
                fprintf(fout, "%3.9f\t%3.9f\n", (double)buf[0] / arg1, (double)buf[1] / arg1);
            }
            else if (outFmt == OPT_OWJ)
            {
                sf=sym/15360;
                sf%=5;
                fread(buf2, sizeof(short), 2, fin2);
                
                //if(sf==0 || sf==1 || sf==4)
                if((sym>=0 && sym<26624)
                  ||(sym>=15360*4 && sym<15360*5))
                {
                    fprintf(fout, "%i\t%i\n", (int) buf[0], (int) buf[1]);
                }
                else
                {
                    fprintf(fout, "%i\t%i\n", (int) buf2[0], (int) buf2[1]);
                }
                sym++;
                sym %= (15360*5);
                
            }
            else if (outFmt == OPT_OARR)
            {
                fprintf(fout, "%i, %i,\n", (int) buf[0], (int) buf[1]);
            }
            else if(outFmt == OPT_OSAM)
            {
                //l++;
                //if((l>(15360*10*92))&&(l<(15360*10*96)))
                {
                    if((j==0)&&(k<1000))
                    {
                        fclose(fout);
                        fopen_s(&fout, out_file[k], "w");
                    }
                    j++;
                    if(fout)
                    fprintf(fout, "%i %i\n", (int) buf[0], (int) buf[1]);
                    if(j==1024*15)
                    {
                        k++;
                        j=0;
                        //fclose(fout);
                    }
                }
            }  
            else if(outFmt == OPT_OUT)
            {
                fprintf(fout, "%i, %i,\n", (int) buf[0], (int) buf[1]);
            }
        }
    }

    fclose(fin);
    if(argc>5)fclose(fin2);
    fclose(fout);

    printf("Done\n");

    return 0;
}

