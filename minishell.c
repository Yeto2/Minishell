/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:59:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/04/24 20:37:55 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print list as a table

void print_list(t_env *list)
{
    t_env *tmp = list;
    while (tmp)
    {
        printf(" (%s)  ->  ", tmp->key);
        if(tmp->value == PIPE)
            printf("PIPE\n");
        else if(tmp->value == SPACE)
            printf("SPACE\n");
        else if(tmp->value == IN)
            printf("IN\n");
        else if(tmp->value == HEREDOC)
            printf("HEREDOC\n");
        else if(tmp->value == OUT)
            printf("OUT\n");
        else if(tmp->value == APPEND)
            printf("APPEND\n");
        else if(tmp->value == SNGL_Q)
            printf("Sgl_q\n");
        else if(tmp->value == DBL_Q)
            printf("Dbl_q\n");
        else if(tmp->value == VAR)
            printf("VAR\n");
        else if(tmp->value == CMD)
            printf("CMD\n");
        else if(tmp->value == DBL_VAR)
            printf("DBL_VAR\n");
        tmp = tmp->next;
    }

}

// Function to take input 
// int takeInput(char* str) 
// { 
//     char* buf;
//     char prompt[12] = "Minishell> ";
//     buf = readline(prompt); 
//     if (ft_strlen(buf) != 0) { 
//         add_history(buf); 
//         ft_strcpy(str, buf); 
//         return 0; 
//     } else { 
//         return 1; 
//     } 
// }

// int is_pipe(char *line)
// {
//     int i = 0;
//     while (line[i] != '\0')
//     {
//         if (line[i] == '|')
//             return (1);
//         i++;
//     }
//     return (0);
// }
int is_space(char c)
{
    return (c == ' ' || (c > 9 && c < 13));
}

int is_special(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"' || c == '$' || is_space(c));
}
int find_char(char *str, char c)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (0);
}
int is_alnum(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_');
}

void processline(char *line, t_env **list)
{
    int i;
    int start;
    int end;
    
    start = 0;
    end = 0;
    i = 0;
    
    while (line[i] != '\0')
    {
        if (line[i] == '|')
            lst_add_back(list, lst_new(ft_substr(line, i++, 1), PIPE));
        else if (is_space(line[i]))
        {
            while (is_space(line[i + 1]))
                i++;
            lst_add_back(list, lst_new(ft_substr(line, i++, 1), SPACE));
        }
        else if (line[i] == '<')
        {
            if (line[i + 1] == '<')
                lst_add_back(list, lst_new(ft_substr(line, i++, 2), HEREDOC)); // 2
            else
                lst_add_back(list, lst_new(ft_substr(line, i, 1), IN));
            i++;
        }
        else if (line[i] == '>')
        {
            if (line[i + 1] == '>')
                lst_add_back(list, lst_new(ft_substr(line, i++, 2), APPEND));
            else
                lst_add_back(list, lst_new(ft_substr(line, i, 1), OUT));
            i++;
        }
        else if (line[i] == '\'')
        {
            if (line[i + 1] == '\'')
                lst_add_back(list, lst_new(ft_substr(line, i++, 2), SNGL_Q));
            else
            {
                start = i;
                end = find_char(line + i + 1, '\'');
                if(end)
                    lst_add_back(list, lst_new(ft_substr(line, start, end + 2), SNGL_Q));
                else
                    print_error("Error: missing single quote\n");
                i += end + 1;
            }
            i++;
            start = 0;
            end = 0;
        }
        else if (line[i] == '\"')
        {
            if (line[i + 1] == '\"')
                lst_add_back(list, lst_new(ft_substr(line, i++, 2), DBL_Q));
            else
            {
                start = i;
                end = find_char(line + i + 1, '\"');
                if(end)
                    lst_add_back(list, lst_new(ft_substr(line, start, end + 2), DBL_Q));
                else
                    print_error("Error: missing double quote\n");
                i += end + 1;
                start = 0;
                end = 0;
            }
            i++;
        }
        else if(line[i] == '$' && (line[i + 1] >= '0' && line[i + 1] <= '9'))
        {
            lst_add_back(list, lst_new(ft_substr(line, i++, 2), VAR));
            i++;
        }
        else if(line[i] == '$' && line[i + 1] == '$')
        {
            lst_add_back(list, lst_new(ft_substr(line, i++, 2), DBL_VAR));
            i++;
        }
        else if (line[i] == '$') // ---------------> prob in $.HOME  ~~~~ fixed
        {
            if (!is_alnum(line[i + 1]))
                lst_add_back(list, lst_new(ft_substr(line, i++, 1), CMD));
            else
            {
                start = i;
                end = i;
            printf("$ ---> '%c'\n", line[i]);
                while (is_alnum(line[end + 1]))
                    end++;
            printf("end ---> '%c' , %d\n", line[end], end);
                lst_add_back(list, lst_new(ft_substr(line, start, end),VAR));
                i = end;
                start = 0;
                end = 0;
            }
            i++;
        }
        else // prowem in a$cmd.a  ~~~~ fixed
        {
            start = i;
            while (line[i] && !is_special(line[i + 1]))
                i++;
            printf("cmd ---> '%c'\n", line[i]);
            lst_add_back(list, lst_new(ft_substr(line, start, i - start + 1), CMD));
            i++;
            start = 0;
        }
        
    }//----------------------> problem in $"command" and $'command' : dollar should not be printed  !!
    
}

// Main function
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;
    char *line;
    // int execFlag = 0;
    t_env *list;
    list = NULL;
    
    // initshell(env);
    while (1)
    { 
        line =  readline("Minishell> "); 
        if (ft_strlen(line) != 0)
            add_history(line); 
        // if (takeInput(line))
        //     continue;

        processline(line , &list);
        printf("\n-----------\n");
        print_list(list);
        
        // printf("---->%d\n", execFlag);
        free(line);
        list = NULL;
    }
}