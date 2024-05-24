#define MAXSIZE 100          //假设非零元个数的最大值为100
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//icoding中的串替换
int str_equal(char *in,int startpos,int*end_pos,char*target){
    int i=0;
    //endpos存储相同部分最后一个字母后一个的下标
    *end_pos = -1;
    int scanner = startpos;
    while(target[i]!='\0'){
        if(target[i]!=in[scanner]){
            break;
        }
        else{
            i++;
            scanner++;
        }
    }
    if(target[i]=='\0'){
        *end_pos = scanner;
    }
    return *end_pos;
}
int str_replace(const char *in, char *out, int outlen, const char *oldstr, const char *newstr){
    int new_len = 0;
    while (newstr[new_len]!='\0')
    {
        new_len++;
    }
    int already_changed=0;
    int old_len=0;
    while(oldstr[old_len]!='\0'){
        old_len++;
    }
    int ori_len=0;
    while(in[ori_len]!='\0'){
        ori_len++;
    }
    int len = outlen-1;
    for(int i=0;i<outlen;i++){
        out[i] = '\0';
    }
    int writer=0;
    for(int j=0;j<ori_len;){
        int save = -1;
        int *saver;
        saver = &save;
        if(str_equal(in,j,saver,oldstr)!=-1){//说明相等
            if(ori_len-(already_changed+1)*old_len+(already_changed+1)*new_len<=len){
                for(int k=0;k<new_len;k++){
                    out[writer] = newstr[k];
                    writer++;
                }
                j=*saver;
                already_changed++;
            }
            else{
                for(;j<ori_len;j++){
                    out[writer] = in[j];
                    writer++;
                }
                break;
            }
        }
        else{
            out[writer] = in[j];
            writer++;
            j++;
        } 
    }
    return already_changed;
}

//版本2：
int str_replace2(const char *in, char *out, int outlen, const char *oldstr, const char *newstr){
 int new_len = 0;
    while (newstr[new_len]!='\0')
    {
        new_len++;
    }
    int already_changed=0;
    int old_len=0;
    while(oldstr[old_len]!='\0'){
        old_len++;
    }
    int ori_len=0;
    while(in[ori_len]!='\0'){
        ori_len++;
    }
    int len = outlen-1;
    for(int i=0;i<outlen;i++){
        out[i] = '\0';
    }
    int writer=0;
    int j=0;
    for(;j<ori_len;){
        int k=0;
        if(in[j]==oldstr[k]){
            int plot = j;
            while(oldstr[k]!='\0'){
                if(in[j]==oldstr[k]){
                    j++;
                    k++;
                }
                else{
                    break;
                }
            }
            if(oldstr[k]=='\0'){
                if(ori_len-(already_changed+1)*old_len+(already_changed+1)*new_len<=len){
                    already_changed++;
                    for(int m=0;m<new_len;m++){
                        out[writer] = newstr[m];
                        writer++;
                    }
                }
                else{
                    while(plot<ori_len){
                        out[writer] = in[plot];
                        plot++;
                        writer++;
                    }
                    break;
                }
            }
            else{
                while(plot!=j){
                    out[writer]=in[plot];
                    plot++;
                    writer++;
                }
            }
        }
        else{
            out[writer] = in[j];
            writer++;
            j++;
        }
        
    }       
    return already_changed;
}
int binary_equal(char*in,char*target){
    int len_in = strlen(in);
    int tar_len = strlen(target);
    int flag=0;
    if(tar_len!=len_in){
        return -1;
    }
    else{
        int k=0;
        int j=0;
        int in_search = len_in-1;
        int tar_search = tar_len-1;
        while(1){
            if(in_search<k){
                flag=1;
                break;
            }
            if(in[k]!=target[j]||in[in_search]!=target[tar_search]){
                return flag;
            }
            else{
                in_search--;
                tar_search--;
                j++;
                k++;
            }
        }
    }
    return flag;
}
int main(){
    printf("%d",binary_equal("123","123"));
    return 0;
}