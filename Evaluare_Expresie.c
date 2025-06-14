#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
void Pop(int *top){
        if((*top)<=-1)
            printf("Stack Underflow ");
        else 
            (*top)--;

}

void Push(char *stack , int *top, char item){
    if(*top == MAX-1)
        printf("Stack Overflow");
    else{
        (*top) ++;
        *(stack + *top) = item;
    }

}

void PushInt(int *stack , int *top, int item){
    if(*top == MAX-1)
        printf("Stack Overflow");
    else{
        (*top) ++;
        *(stack + *top) = item;
    }

}

int VerifOp(char op){
    if(op == '+' || op == '-')
    return 2;
    if(op == '*' || op == '/')
    return 1;
}

int main(){
    
    char fp[100],st[100],saux[150],s[150];//stivele folosite pentru implementarea formei poloneze post fixate
    int top_st=-1,top_fp=-1, nr_operanzi=0;
    int op[100],top_op=-1;//stiva folosita pentru efectuarea operatiilor
    
    //Citim expresia noastra si adaugam paranteze pentru usurarea calculului
    scanf("%s",saux);
    s[0]='(';
    strcat(s,saux);
    s[strlen(s)]=')';
    s[strlen(s)]='\0';
    //Se creeaza forma poloneza post fixata
    for(int i=0;i<strlen(s);i++)
        {
            if(isalpha(s[i])){
                Push(fp,&top_fp,s[i]);
                nr_operanzi++;
            }
            else if(s[i] == '(')
                Push(st,&top_st,s[i]);
            else if(s[i] == ')'){
                while(  st[top_st] !=  '(')
                {
                    Push(fp,&top_fp,st[top_st]);
                    Pop(&top_st);
                }
                Pop(&top_st);

            }
            else {
                if(VerifOp(s[i])==2)
                {
                    if(VerifOp(st[top_st])==1)
                        {
                        Push(fp,&top_fp,st[top_st]);
                        Pop(&top_st);
                        }

                    Push(st,&top_st,s[i]);
                }
                else {
                    if(VerifOp(st[top_st])==1){
                    Push(fp,&top_fp,st[top_st]);
                    Pop(&top_st);
                    Push(st,&top_st,s[i]);
                    }
                    else{
                        Push(st,&top_st,s[i]);
                    }
                }
            }
            

        }
        
        fp[top_fp+1]='\0';
        printf("Forma poloneza este: ");
        for(int i = 0;i<strlen(fp);i++)
            printf("%c",fp[i]);
        printf("\n");
        //parcurgem stiva fp de la stanga la dreapta si efectuam operatiile folosind stiva op
        for(int i = 0;i<strlen(fp);i++){
            if(isalpha(fp[i]))
            scanf("%d",&op[++top_op]);
            else
            {   
                int nr2 = op[top_op];
                Pop(&top_op);
                int nr1 = op[top_op];
                Pop(&top_op);
                if(fp[i]=='+')
                    PushInt(op,&top_op,nr1+nr2);
                else if(fp[i]=='-')
                    PushInt(op,&top_op,nr1-nr2);
                else if(fp[i]=='*')
                    PushInt(op,&top_op,nr1*nr2);
                else if(fp[i]='/')
                    PushInt(op,&top_op,nr1/nr2);
                    

            }
        }
        printf("%d",op[0]);
        

    return 0;
    
}
