#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void saveMarks(int x, int array1[]);
void tabulateMarks(int array2[][2]);

int main(){
    int choice=1;
    int count=0;
    int i, id;
    int credits=0;
    int credits1=0;
    int credits2=0;
    int total1=0;
    int total2=0;
    int modules1=0;
    int modules2=0;
    int marks[37];
    int results[40][2]={0};
    float weigh, avg1, avg2;

    FILE* fmarks;
    FILE* fresults;

    while(choice!=2){
        printf("\n**********************************************************\n");
        printf("\t1.Enter student's marks.\n\t2.Quit.\n");
        printf("**********************************************************\n");
        printf("Your Choice: ");
        scanf("%d", &choice);
        if(choice == 1){
            //year one
            printf("\nEnter student ID number: ");
            scanf("%d", &id);
            results[count][0]=id;
            printf("\nThe following are the modules of Year One:\n");
            printf("**NOTE: All the following modules are compulsory.\n\n");
            printf("H61IIC Introduction to Electronic Engineering\n");
            printf(" MM1DM Design and Manufacture 1\n");
            printf("H61LSB Laboratory and Presentation Skills B\n");
            printf("H61ICT Introduction to Circuits\n");
            printf("H61ICP Introduction to Computer Engineering\n");
            printf(" MM1MS Mechanics of Solids 1\n");
            printf("HG1M11 Engineering Mathematics 1\n");
            printf("H61IAL Introduction to Electrical Engineering\n");
            printf("HG1M12 Engineering Mathematics 2\n");
            printf(" MM1DM Dynamics of Mechanical Systems\n\n");
            printf("Enter student's marks for the above modules:\n");
            for(i=0; i<10; i++){
                scanf("%d", &marks[i]);
                if(marks[i] >= 40){
                    if(i == 0 || i == 1)
                        credits += 20;
                    else
                        credits += 10;
                }
            }
            if(credits<100){
                printf("\n\nStudent failed to progress to Year Two.\n");
            }
            else{
                printf("\nStudent progressed to Year Two.\n");
                //year two
                printf("\nThe following are the modules of Year Two:\n");
                printf("**NOTE: All the following modules are compulsory.\n\n");
                printf("MM2DM Design and Manufacture 2\n");
                printf("MM1TF1 Thermodynamics & Fluid Mechanics 1\n");
                printf("HG2ME1 Mathematical Techniques for Electrical and Electronic Engineers 1\n");
                printf("H62SPC Signal Processing and Control Engineering\n");
                printf("H62PSE Power Supply Electronics\n");
                printf("H62NUM Numerical Methods and Contextual Electrical and Electronic Engineering Mathematics\n");
                printf("H62ELD Electronic Engineering\n");
                printf("Electrical Engineering Design Project\n\n");
                printf("Enter student's marks for the above modules:\n");
                for(i=10;i<18; i++){
                    scanf("%d", &marks[i]);
                    if(marks[i] >= 40){
                        total1 += marks[i];
                        modules1++;
                        if(i == 10|| i == 11|| i == 13|| i == 16)
                            credits1 += 20;
                        else
                            credits1 += 10;
                    }
                }
                if(credits1>=100 && (total1/modules1)>=55){
                    printf("\nStudent progressed to Year Three.\n");
                    //year three
                    printf("\nThe following are the modules of Year Three:\n\n");
                    printf("Compulsory Modules:\n");
                    printf("H63MGP Mechatronics Group Project (only for M.Eng students)\n");
                    printf("H63TYP Third year project\n");
                    printf("H63CSD Control Systems Design\n");
                    printf("H63NEN Neural Networks\n");
                    printf("H63RDC Robotics Dynamics and Control\n");
                    printf("H63MLB Mechatronics Laboratory\n");
                    printf("H63RAR Risk and Reliability\n");
                    printf("H13IDT Industrial training***\n");
                    printf("\nOptional Modules:\n");
                    printf("H63EMA Electrical Machines\n");
                    printf("H63END Electronic Design\n");
                    printf("H63ECH Embedded Computing\n");
                    printf("H63PED Power Electronic Design\n");
                    printf("H63EDR Energy Conversion for Motor and Generator Drives\n");
                    printf("H63VIC Visual Information Computing\n");
                    printf("H63REN Renewable Generation Technologies and Control\n");
                    printf(" MM4MM Material Models and Modes of Failure \n");
                    printf("HG4MEM Mathematics for Engineering Management \n");
                    printf("MM3AD Advanced Dynamics of Machines\n");
                    printf("MM3AUT Introduction to Automotive Technology\n");
                    printf("N12402 Marketing strategy \n\n");
                    printf("Enter student's marks for the above modules:\n");
                    printf("**NOTE: Enter '-1' if the student did not take the module.\n");
                    for(i=18;i<37; i++){
                        scanf("%d", &marks[i]);
                        if(marks[i] >= 40){
                            total2 += marks[i];
                            modules2++;
                            if(i == 18|| i == 19)
                                credits2 += 30;
                            else
                                credits2 += 10;
                        }
                    }
                    saveMarks(id, marks);
                    if(credits2>=100){
                        avg1 = total1 / modules1;
                        avg2 = total2 / modules2;
                        weigh = (avg1)/3 + (avg2 * 2)/3;
                        if(weigh>=0 && weigh<40)
                            printf("\nStudent has failed.\nTotal of the last two years is: %.2f%\n", weigh);
                        else if(weigh>=40 && weigh<50)
                            printf("\nStudent has passed [Third Class].\nTotal of the last two years is: %.2f%\n", weigh);
                        else if(weigh>=50 && weigh<60)
                            printf("\nStudent has passed [Second Class, division II].\nTotal of the last two years is: %.2f%\n", weigh);
                        else if(weigh>=60 && weigh<70)
                            printf("\nStudent has passed [Second Class, division I].\nTotal of the last two years is: %.2f%\n", weigh);
                        else if(weigh>=70 && weigh<=100)
                            printf("\nStudent has passed [First Class].\nTotal of the last two years is: %.2f%\n", weigh);
                    }
                    else
                        printf("\nStudent has failed to progress to Year Four.\n");
                    results[count][1]=weigh;
                    tabulateMarks(results);
                }
            }
        }
        count++;
    }
    return 0;
}

void saveMarks(int x, int array1[]){
    FILE* fmarks = fopen("marks.dat", "a");
    int i;
    fprintf(fmarks, "\n%d", x);
    for(i=0; i<37; i++){
        if(array1[i] == -1)
            fprintf(fmarks, ",");
        else
            fprintf(fmarks, ",%d", array1[i]);
    }
    fclose(fmarks);
}
void tabulateMarks(int array2[][2]){
    FILE* fresults = fopen("results.txt", "w");
    int i, j, n, temp;
    for(i=0; i<40; i++){
        for(j=0; j<39; j++){
            if(array2[j][1]<array2[j+1][1]){
                temp=array2[j+1][1];
                array2[j+1][1]=array2[j][1];
                array2[j][1]=temp;
            }
        }
    }
    fprintf(fresults, "ID:\t\tFinal Mark:\n");
    for(n=0; n<40; n++){
        fprintf(fresults, "\n%d %20d", array2[n][0], array2[n][1]);
    }
    fclose(fresults);
}
