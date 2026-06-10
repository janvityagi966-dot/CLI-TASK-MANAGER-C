#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_Tasks 100
#define Max_Title 100
#define file_Name "Tasks.txt"
// Structure to represent a Task
typedef struct 
{
    int ID;
    char title[Max_Title];
    int priority; //1=High,2=Medium,3=Low
    int is_Completed;//1=completed,0=Pending
}Task;
 Task tasks[Max_Tasks];
 int task_count=0;
 void LOAD_TASKS(void);
 void ADD_TASKS(void);
 void VIEW_TASKS(void);
 void UPDATE_TASKS(void);
 void DELETE_TASKS(void);
 void SAVE_TASKS(void);
 void OPEN_NOTEPAD(void);
 void SHOW_DATE(void);
 void SHOW_TIME(void);
 void OPEN_WEBSITE(void);

 int main()
 {
    int choice;
    LOAD_TASKS();
    while(1)
    {
        printf("\n *******CLI TASK MANAGER*********\n");
        printf("\n1.Add Task\n");
        printf("\n2.View Task\n");
        printf("\n3.Update(Mark Task as completed) Task\n");
        printf("\n4.Delete Task\n");
        printf("\n5.Open Notepad\n");
        printf("\n6.Show Date\n");
        printf("\n7.Show Time\n");
        printf("\n8.Open Website\n");
        printf("\n9.Exit\n");
        printf("\n Enter your Choice(1-9)\n");
       if (scanf("%d",&choice)!=1)
        {
            printf("Invalid Input. Please Enter a Number \n");
            while(getchar()!='\n');   // clear input Buffer
            continue;
        }
        getchar();//consume newline character left by scanf
        switch(choice)
        {
            case 1: ADD_TASKS();
            break;
            case 2: VIEW_TASKS();
            break;
            case 3: UPDATE_TASKS();
            break;
            case 4: DELETE_TASKS();
            break;
            case 5: OPEN_NOTEPAD();
            break;
            case 6: SHOW_DATE();
            break;
            case 7: SHOW_TIME();
            break;
            case 8: OPEN_WEBSITE();
            break;
            case 9: SAVE_TASKS();  // save tasks before exiting
            printf("Tasks saved successfully, GOODBYE! \n");
            exit(0);
            default:
            printf("\n Wrong Choice");
        }
    }
    return(0);
}
void ADD_TASKS(void)
{
    if (task_count >= Max_Tasks)
    {
        printf("\n TASK LIST IS FULL! \n ");
        return;
    }
    Task new_task;
    new_task.ID = (task_count == 0) ? 1 : tasks[task_count-1].ID + 1;
    printf("\n Enter Task Title: ");
    if (fgets(new_task.title, Max_Title,stdin) == NULL)
    {
        new_task.title[0] = '\0';
    }
    else
    {
        new_task.title[strcspn(new_task.title, "\n")] = '\0';
    }
    printf("\n Enter Priority(1-High,2-Medium,3-Low): ");
    if (scanf("%d", &new_task.priority) != 1 ||
        new_task.priority < 1 || new_task.priority > 3)
    {
        new_task.priority = 2;
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    new_task.is_Completed = 0;
    tasks[task_count] = new_task;
    task_count++;
    SAVE_TASKS();
    printf("\n TASK ADDED SUCCESSFULLY");
}
void VIEW_TASKS(void)
    {
        if(task_count==0)
        {
            printf("\n NO TASKS FOUND");
            return;
        }
        printf("\n------------------------------------------------------------------------------\n");
        printf("\n %-5s,%-25s,%-10s,%-10s\n", "ID","TITLE","PRIORITY","STATUS");
        printf("\n------------------------------------------------------------------------------\n");
        for(int i=0;i<task_count;i++)
        {
            char priority_str[10];
            if(tasks[i].priority==1)strcpy(priority_str,"HIGH");
            else if(tasks[i].priority==2)strcpy(priority_str,"MEDIUM");
            else strcpy(priority_str,"LOW");
            printf("\n %-5d %-25s %-10s %-10s\n",
                   tasks[i].ID,
                   tasks[i].title,
                   priority_str,
                   tasks[i].is_Completed ? "DONE" : "PENDING");
        }
        printf("\n------------------------------------------------------------------------------------\n");
    }
    void UPDATE_TASKS(void)
    {
        if (task_count == 0)
        {
            printf("\n NO TASKS TO UPDATE");
            return;
        }
        int target_ID, found = 0;
        printf("\n Enter the Task ID to mark as Complete: ");
        scanf("%d", &target_ID);
        for (int i = 0; i < task_count; i++)
        {
            if (tasks[i].ID == target_ID)
            {
                tasks[i].is_Completed = 1;
                found = 1;
                SAVE_TASKS();
                printf("\n Task ID %d marked as Completed!\n", target_ID);
                break;
            }
        }
        if (!found)
        {
            printf("TASK %d ID NOT FOUND", target_ID);
        }
    }
void DELETE_TASKS(void)
{
             if(task_count==0)
        {
            printf("\n NO TASKS TO DELETE");
            return;
        }
        int target_ID,found=0;
        printf("\n Enter the Task ID to delete: ");
        scanf("%d",&target_ID);
        for(int i=0;i<task_count;i++)
        {
            if(tasks[i].ID==target_ID)
            {
                found=1;
                for(int j=i;j<task_count-1;j++)
                {
                    tasks[j]=tasks[j+1];
                }
                task_count--;
                SAVE_TASKS();
                printf("\n Task ID %d deleted successfully",target_ID);
                break;
            }
        }
        if(!found)
    {
        printf("TASK %d ID NOT FOUND",target_ID);
    }
}
void SAVE_TASKS(void)
{
    FILE *file = fopen(file_Name, "w");
    if (file == NULL)
    {
        printf("\n ERROR SAVING TASKS TO FILE\n");
        return;
    }
    for (int i = 0; i < task_count; i++)
    {
        fprintf(file, "%d|%s|%d|%d\n", tasks[i].ID, tasks[i].title,
                tasks[i].priority, tasks[i].is_Completed);
    }
    fclose(file);
}
void LOAD_TASKS(void)
{
    FILE *file = fopen(file_Name, "r");
    if (file == NULL)
    {
        return;
    }
    task_count = 0;
    while (task_count < Max_Tasks &&
           fscanf(file, "%d|%99[^|]|%d|%d\n",
                  &tasks[task_count].ID,
                  tasks[task_count].title,
                  &tasks[task_count].priority,
                  &tasks[task_count].is_Completed) == 4)
    {
        task_count++;
    }
    fclose(file);
}   
void OPEN_NOTEPAD(void)
{
    system("Notepad");
    printf("\n Notepad Opened");
}
void SHOW_DATE(void)
{
    char command[20]="date/t";
    system(command); 
}
void SHOW_TIME(void)
{
    char command[20]="time/t";
    system(command); 
}
void OPEN_WEBSITE()
 {
    printf("\n1. Google\n2. YouTube\n3. GitHub\n4. Custom URL\n");
    printf("Choose: ");
    int ch;
    scanf("%d", &ch);
    getchar();

    if(ch == 1) system("start \"\" \"https://www.google.com\"");
    else if(ch == 2) system("start \"\" \"https://www.youtube.com\"");
    else if(ch == 3) system("start \"\" \"https://www.github.com\"");
    else if(ch == 4) {
        char url[100];
        printf("Complete URL with https:// : ");
        scanf("%s", url);
        getchar();
        char cmd[150];
        sprintf(cmd, "start \"\" \"%s\"", url);
        system(cmd);
    }
    else printf("Wrong Option\n");

    printf("Done!\n");
}

    

    
