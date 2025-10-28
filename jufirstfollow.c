#include<stdio.h>
#include<string.h>
#define max 50
char firsts[max][max], follows[26][max],prods[26][max];
int n;
int is_first_done[26], is_follow_done[26];
int is_terminal (char c)

{
    return !(c>='A' && c<='Z');
}

int exists(char arr[],char c)
{
    for(int i=0;arr[i]!='\0';i++)
    {
        if(arr[i]==c)
        {
            return 1;
        }
    }
    return 0;
}

void first(char nonterm)
{
    char temp[max]="";
    for(int i=0;i<n;i++)
    {
        if(prods[i][0]==nonterm)
        {
            int j=2;
            int epsilon_found=0;
            while(prods[i][j]!='\0')
            {
                char sym=prods[i][j];
                if(is_terminal(sym))
                {
                    if(!exists(temp,sym))
                    {
                        strncat(temp,&sym,1);
                    }
                    break;
                }
                else{
                    if(!is_first_done[sym-'A'])
                    {
                        first(sym);
                    }
                    int k=0;
                    while(firsts[sym-'A'][k]!='\0')
                    {
                        char x=firsts[sym-'A'][k];
                        if(x=='e')
                        {
                            epsilon_found=1;
                        }
                        else{
                            if(!exists(temp,x))
                            {
                                strncat(temp,&x,1);
                            }
                        }
                        k++;
                    }
                    if(!epsilon_found)
                    {
                        break;
                    }
                    else{
                        j++;
                    }
                }
            }
            if(prods[i][j]=='\0'||epsilon_found)
        {
            if(!exists(temp,'e'))
            {
                strncat(temp,"e",1);
            }
        }
        }
        
    }
    strcpy(firsts[nonterm-'A'],temp);
    is_first_done[nonterm-'A']=1;
}
void follow(char nonterm)
{
    char temp[max]="";
    if(nonterm==prods[0][0])
    {
        strncat(temp,"$",1);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=2;prods[i][j]!='\0';j++)
        {
            if(prods[i][j]==nonterm)
            {
                int next=j+1;
                int epsilon_found=0;
                if(prods[i][next]!='\0')
                {
                    char next_sym=prods[i][next];
                    if(is_terminal(next_sym))
                    {
                        if(!exists(temp,next_sym))
                        {
                            strncat(temp,&next_sym,1);
                        }
                    }
                    else{
                        if(!is_first_done[next_sym-'A'])
                        {
                            first(next_sym);
                        }
                        int k=0;
                        while(firsts[next_sym-'A'][k]!='\0')
                        {
                            char x=firsts[next_sym-'A'][k];
                            if(x=='e')
                            {
                                epsilon_found=1;
                            }
                            else{
                                if(!exists(temp,x))
                                {
                                    strncat(temp,&x,1);
                                }
                            }
                            k++;
                        }
                        if(epsilon_found)
                        {
                            char lhs=prods[i][0];
                            if(lhs!=nonterm)
                            {
                                if(!is_follow_done[lhs-'A'])
                                {
                                    follow(lhs);
                                }
                            }
                            int m=0;
                            while(follows[lhs-'A'][m]!='\0')
                            {
                                char y=follows[lhs-'A'][m];
                                if(!exists(temp,y))
                                {
                                    strncat(temp,&y,1);
                                }
                                m++;
                            }
                        }
                    }
                }
                else{
                    char lhs=prods[i][0];
                    if(lhs!=nonterm)
                    {
                        if(!is_follow_done[lhs-'A'])
                        {
                            follow(lhs);
                        }
                        int m=0;
                        while(follows[lhs-'A'][m]!='\0')
                        {
                            char y=follows[lhs-'A'][m];
                            if(!exists(temp,y))
                            {
                                strncat(temp,&y,1);
                            }
                            m++;
                        }
                    }
                }
            }

        }
    }
    strcpy(follows[nonterm-'A'],temp);
    is_follow_done[nonterm-'A']=1;
}
void main()
{
    printf("Enter no.of productions: ");
    scanf("%d",&n);
    printf("Enter productions: ");
    for(int i=0;i<n;i++)
    {
        scanf("%s",prods[i]);
    }

    for(int i=0;i<n;i++)
    {
        char lhs=prods[i][0];
        if(!is_first_done[lhs-'A'])
        {
            first(lhs);
        }
    }
    for(int i=0;i<n;i++)
    {
        char lhs=prods[i][0];
        if(!is_follow_done[lhs-'A'])
        {
            follow(lhs);
        }
    }

    printf("FIRST SETS:\n");
    int printed[26]={0};
    for(int i=0;i<n;i++)
    {
        char lhs=prods[i][0];
        if(!printed[lhs-'A'])
        {
            printf("First(%c)={%s}\n",lhs,firsts[lhs-'A']);
            printed[lhs-'A']=1;
        }
    }
    memset(printed,0,sizeof(printed));
    printf("FOLLOW SETS:\n");
    for(int i=0;i<n;i++)
    {
        char lhs=prods[i][0];
        if(!printed[lhs-'A'])
        {
            printf("Follow(%c)={%s}\n",lhs,follows[lhs-'A']);
            printed[lhs-'A']=1;
        }
    }
}
