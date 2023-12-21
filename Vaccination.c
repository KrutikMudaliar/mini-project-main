#include <stdio.h>
typedef struct patient
{
    // Structure that stores all details of a patient
    int age ;
    long aadhar ;
    int ph_number ;
    int secret_code ;
    int vaccine_type ;
    int vaccine_doses ;
} patient_details;
// variable patient_log that stores details of upto 1000 patients
patient_details patient_log[1000];



int regist_status(long entred_adhar)
{
    // Checks for registration details of new patients
    patient_log[0].aadhar = entred_adhar;
    int i = 1;
    while (i <= 1000)
    {
        if (patient_log[i].aadhar == patient_log[0].aadhar)
        {
            if (patient_log[i].vaccine_type == 0)
                return 0; // this means registred but not logged in
            else
                return 1; // registred and logeed in
        }
        i++;
    }
    return -1; // not registred
}

// Checks how many doses should be given
int vaccine_status(int i)
{

    if (patient_log[i].vaccine_doses == 0)
    { // not taken any dose
        patient_log[i].vaccine_doses++;
        return 1;
    }
    else if (patient_log[i].vaccine_doses == 1)
    { // taken 1 dose
        patient_log[i].vaccine_doses++;
        return 2;
    }
    else if (patient_log[i].vaccine_doses == 2)
    { // taken 2 doses
        return 3;
    }
    else
        return 0;
}

// Program begins from this section
int main()
{

    int status;         // A return parameter to check status of patient
    long entred_adhar;  // Variable that stores patient's aadhar number
    int v1 = 0, v2 = 0; //Vaccine type 1 and 2 quantity

    

    int attmpt = 1000; // Variable that determines the total number of execution by EOD
    while (attmpt > 0)
    {

    apply:
        printf("\n\t\t\t\t\t\tLet's get vaccinated!!!\n");
        printf("\t\t\t\t\t\tEnter your aadhar number:");
        scanf("%lld", &entred_adhar);

        if (entred_adhar == 3112) // secret code to view results
        {
            goto results;
        }

        status = regist_status(entred_adhar);
        int i, j = 0, vstat = 0, vaccine_choice = 0, pno;

        i = 1;
        while (i <= 1000)
        {
            if (patient_log[i].aadhar == entred_adhar)
                j = i; // for storing the idex of stored adhar
            i++;
        }

        if (status == -1) // for first time registration
        {
            
            i = 1;
            while (i <= 1000)
            {
                if (patient_log[i].aadhar == 0)
                {
                    printf("\t\t\t\t\t\tFill details for registration\n");
                    patient_log[i].aadhar = patient_log[0].aadhar;
                    printf("\t\t\t\t\t\tEnter your phone number: ");
                    scanf("%d", &patient_log[i].ph_number);
                    printf("\t\t\t\t\t\tEnter your age: ");
                    scanf("%d", &patient_log[i].age);
                    printf("\t\t\t\t\t\tEnter your secret code: ");
                    scanf("%d", &patient_log[i].secret_code);
                    break;
                }
                i++;
            }
            printf("\t\t\t\t\t\tCredentials saved, log in again\n");
            goto apply;
        }
        else if (status == 0) // for first time logging in
        {
            //Verification
            printf("\t\t\t\t\t\tConfirm user, enter ph.number\n\t\t\t\t\t\t");
        prv1:
            scanf("%d", &pno);
            if (pno == patient_log[j].ph_number)
                goto nxt1;
            else
                printf("\t\t\t\t\t\tWrong credentials, try again\n");
            goto prv1;
        nxt1:
            printf("\t\t\t\t\t\tTime for vaccine\n\t\t\t\t\t\tSelect type\n");
            printf("\t\t\t\t\t\t1:Covishield\n\t\t\t\t\t\t2:Covaxin\n\t\t\t\t\t\t");
            scanf("%d", &vaccine_choice);
            if (patient_log[j].vaccine_type == 0)
            {
                switch (vaccine_choice)
                {
                case 1:
                    patient_log[j].vaccine_type = 1;
                    break;
                case 2:
                    patient_log[j].vaccine_type = 2;
                    break;
                default:
                    printf("\t\t\t\t\t\tSelect option 1 or 2\n");
                    break;
                }
            }
        }
        else // logging after taking first dose
        {
            // Verification
            printf("\t\t\t\t\t\tConfirm user, enter ph.number\n\t\t\t\t\t\t");
        prv2:
            scanf("%d", &pno);
            if (pno == patient_log[j].ph_number)
                goto nxt2;
            else
                printf("\t\t\t\t\t\tWrong credentials, try again\n");
            goto prv2;
        }
    nxt2:

        vstat = vaccine_status(j); //Status of patient based on being vaccinated

        if (vstat == 1)
            printf("\t\t\t\t\t\tPlease take your first vaccine\n\t\t\t\t\t\tYou have been vaccinated once\n");
        else if (vstat == 2)
            printf("\t\t\t\t\t\tPlease take your second vaccine\n\t\t\t\t\t\tYou have been vaccinated twice\n");
        else if (vstat == 3)
            printf("\t\t\t\t\t\tYou have completed two dozes of vaccination\n");

        // Count of total number of vaccine vials used
        if (patient_log[j].vaccine_type == 1 && (vstat == 1 || vstat == 2))
            v1++;
        else if (patient_log[j].vaccine_type == 2 && (vstat == 1 || vstat == 2))
            v2++;

        attmpt--;
    }
results:
    printf("\n\t\t\t\t\t\tFinal list of patients and consumed stock of vaccines\n");
    int i = 1;
    while (i <= 1000)
    {
        if (patient_log[i].aadhar != 0)
        {
            printf("\t\t\t\t\t\tP%d Aadhar:%lld\n", i , patient_log[i].aadhar);
            printf("\t\t\t\t\t\tP%d Phone no:%d\n", i , patient_log[i].ph_number);
            printf("\t\t\t\t\t\tP%d Age:%d\n", i , patient_log[i].age);
            printf("\t\t\t\t\t\tP%d Secret code:%d\n", i , patient_log[i].secret_code);
            printf("\t\t\t\t\t\tP%d Vaccine type:%d\n", i , patient_log[i].vaccine_type);
            printf("\t\t\t\t\t\tP%d Vaccine dozes:%d\n\n", i , patient_log[i].vaccine_doses);
            
        }
        i++;
    }
    printf("\n\t\t\t\t\t\tVaccine type 1(COVISHIELD):%d\n", v1);
    printf("\t\t\t\t\t\tVaccine type 2(COVAXIN):%d\n", v2);
    goto apply;
return 0;
}