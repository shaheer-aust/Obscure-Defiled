#include<stdio.h>

struct student
{
    char name[50];
    int roll;
    float marks; 
    float order;
};


int main()
{
    FILE *file;
    file = fopen("U:\\students.txt","w");
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    struct student s[n];

    if(file == NULL){
        printf("File cannot be opened");
        return 1;
    }
    printf(">>>>>.Enter Student's Info");
    for(int i=0;i<n;i++){
        printf("Enter #%d Student's Names: ", i+1);
        scanf("%s",s[i].name);
        printf("Enter #d%d Student's Roll: ",i+1);
        scanf("%d",&s[i].roll);
        printf("Enter #d%d Student's Marks: ",i+1);
        scanf("%f",&s[i].marks):

        fprintf(file,"Name: %s, Roll: %d Marks: %.2f\n",s[i].name,s[i].roll,s[i].marks):
        
    }
    fclose(file);

    int max = s[0].marks;
    for(i=1;i<n;i++){
        if(s[i].marks > max){
            max = s[i].marks;
        }
        int j = i;
    }

    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(s[j].marks < s[j+1].marks){
                struct student temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }

    file = fopen("U:\\students.txt","a");
    fprintf("\n>>>>> Student's in order of marks: \n");
    for(i=0;i<n;i++){
        fprintf(file,"Name: %s, Roll: %d Marks: %.2f\n",s[i].name,s[i].roll,s[i].marks);
    }

    flcose(file);


    file = fopen("U:\\students.txt","r");
    char ch;
    printf("\n>>>>> Student's Info from file: \n");
    while((ch = fgetc(file)) != EOF){
        printf("%c",ch);
    }

    fclose(file);

    return 0;
    


}