#include <netdb.h>

//Look up a domain name
//  1>inet addr - i/p> dotted decimal ascii; o/p> equivqlent ip address in binary
//  2>gethostbyname() - i/p > domain name in ascii ; o/p>returns "struct hostent" in which a field contains host addr in binary

struct hostent{
    char *h_name;           //ascii alphabetic official host name you will pass through gethostbyname()
    char **h_aliases;       //array of other aliases name , NULL terminated array
    
    int h_addrtype;         //type of address being returned(filled later)
    int h_length;           //the length of each addresses in bytes 
    char **h_addr_list;     //list of addresses of host in n/w byte order 
};
#define h_addr h_addr_list[0] //holds the first IP address of host from h_addr_list of Ip addresses

//client can get ip address as
int main()
{
    
    
    //client can get ip address as
    struct hostent *hptr;
    char *exampleHostName = "www.google.com";
    
    if (hptr=gethostbyname(exampleHostName)){
        printf("host ip  = %s",hptr->h_addr);    // Ip address in hptr->h_addr
    }else{
        printf("error");
    }
    
    return 0;
}
