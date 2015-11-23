//Warning! This program writes the output to a file. Any use of this code comes without warranty
#include <gmp.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_BITS 4096

using namespace std;

bool arefactors=0;
unsigned int factorcount = 0;
bool checkFactor(const mpz_t &B, const mpz_t &C);


int main(int argc, char **argv)
{


    mpz_t B;
    int flag;

    mpz_init(B);
    mpz_set_ui(B,0);

    if (argc < 2)
    {
        char inputNumber[MAX_BITS + 1];

        printf("Insert the absolute value of the number that you wish to factor: ");

        char* fcheck = fgets(inputNumber, MAX_BITS, stdin);

        flag = mpz_set_str(B,inputNumber,10);
        assert(flag==0);

    }
    else
    {
        flag = mpz_set_str(B,argv[1],10);
        assert(flag==0);
    }



    printf("The number used is: ");
    mpz_out_str(stdout,10,B);
    printf("\n");

    printf("The Factors are:\n");




    mpz_t C;
    mpz_init(C);
    mpz_set_ui(C,2);




    mpz_t highest;
    mpz_init(highest);
    mpz_root(highest,B,2);
    while (mpz_cmp(highest,C)>0)
    {
        checkFactor(B, C);
        mpz_add_ui(C,C,1);
    }






    if (!arefactors)
    {
        mpz_t temp;
        mpz_init(temp);
        mpz_set_ui(temp,0);

        if (!abs(mpz_cmp_ui(temp,0)))
        {
            printf("Wait, there are no factors other than the number itself and 1!\nYour number must be prime!\n");
            //savefile << "Wait, there are no factors other than itself (" << B << ") and 1!\nYour number must be prime!\n";
        }
        else
        {
            printf("You can't factor 0. I guess 0 is a factor??? T.T\n");
            //savefile << "You can't factor 0. I guess 0 is a factor??? T.T\n";
        }
		mpz_clear(temp);
    }
    else
    {
        printf("There are %d Factors of ", factorcount);// << B << ". The sum of all the factors shown is " << factorsum << ".\n";
        mpz_out_str(stdout,10,B);
        printf("\n");
        //savefile << "There are " << factorcount << " Factors of " << B << ". The sum of all the factors shown is " << factorsum << ".\n";
    }
    mpz_clear(B);
    mpz_clear(C);
    //savefile.close();
    return 0;
}


bool checkFactor(const mpz_t &B, const mpz_t &C)
{
    mpz_t temp;
    mpz_init(temp);
    mpz_set_ui(temp,0);

    mpz_cdiv_r(temp,B,C);
    if (!mpz_cmp_ui(temp,0))
    {
        mpz_out_str(stdout,10,C);
        printf("\t(");
        mpz_cdiv_q(temp,B,C);
        mpz_out_str(stdout,10,temp);

        printf(")\n");

        arefactors=1;
        factorcount+=2;
        return 1;

    }
    mpz_clear(temp);
    return 0;
}

