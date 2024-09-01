
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char* verify_ip(char * ip)
{
    int onebyte = 0;
    int twobyte = 0;
    int threebyte = 0;
    int fourbyte = 0;
    
    while(sscanf(ip , "%d.%d.%d.%d" , &onebyte ,&twobyte, &threebyte , &fourbyte ) != 4)
    {
        printf("veuillez entrer une adresse ip correcte = ");
        scanf("%s" , ip);
    }
   while(onebyte <=0 || onebyte> 255 ||  twobyte <=0 ||   twobyte>255  || threebyte <=0 || threebyte> 255 ||  fourbyte <=0 || fourbyte> 255)
	{
		printf("%d", onebyte);
        printf("veuillez entrer une adresse ip correcte = ");
        scanf("%s" , ip);
    }
    return ip;
}

void address_reseau_broadcast(char* ip, char* mask)
{
    int ip_bytes[4];
    int mask_bytes[4];
    int reseau_bytes[4];
    int broadcast_bytes[4];

    sscanf(ip, "%d.%d.%d.%d", &ip_bytes[0], &ip_bytes[1], &ip_bytes[2], &ip_bytes[3]);
    sscanf(mask, "%d.%d.%d.%d", &mask_bytes[0], &mask_bytes[1], &mask_bytes[2], &mask_bytes[3]);
	printf("\n\t\t --- Etape calcule adresse ip --- \n");
    for(int i = 0; i < 4; i++)
    {
        reseau_bytes[i] = ip_bytes[i] & mask_bytes[i];
        printf("%d.", reseau_bytes[i]);
        printf("%d:", ip_bytes[i]);
        printf("%d;", mask_bytes[i]);
    }

    printf("\n\tAdresse réseau: %d.%d.%d.%d", reseau_bytes[0], reseau_bytes[1], reseau_bytes[2], reseau_bytes[3]);
    for(int i = 0; i < 4; i++)
    {
		if(reseau_bytes[i] == 0)
		{
				broadcast_bytes[i] = 255;
		}
		else
		{
			  broadcast_bytes[i] = reseau_bytes[i];
		 }
       
   
    }

    printf("\n\tAdresse de broadcast: %d.%d.%d.%d\n", broadcast_bytes[0], broadcast_bytes[1], broadcast_bytes[2], broadcast_bytes[3]);
}

void nombre_machine(char * ip)
{
		int onebyte = 0;
		int twobyte = 0;
		int threebyte = 0;
		int fourbyte = 0;
	sscanf(ip , "%d.%d.%d.%d" , &onebyte ,&twobyte, &threebyte , &fourbyte );
	if(onebyte < 128)
		{
				printf("\tnombre de machine =  16 777 214\n");
		}
		if(onebyte >=128 && onebyte < 192)
		{
				printf("\tnombre de machine = 65 534\n");

		}
		if(onebyte <= 192 && onebyte > 224)
		{
				printf("\tnombre de machine  = 254\n");
	
		}


}




char *get_mask(char* a,int f)
{
    int p = 0;
    int s = 0;

    for(int i = 7; i >=0 ; i-- )
    {
        p = pow(2, i);
        s = f - p;
        
        if(s >= 0)
        {
            f = s;
            strcat(a , "1");
        }
        else
        {
            strcat(a, "0");
        }
    }
    
    return a;
}

void get_data_mask()
{
    int i = 0;
    int n = 0;
    int one = 0;
    int two = 0;
    int three = 0;
    int four = 0;
    char b[1000] ;
    char ip[100] = {0};
    char chaine[1000] = {0};
    char mask[100] = {0};
    int error = 0;

	printf("entrer l'adresse ip de format (XXX.XXX.XXX.XXX) = ");
	scanf("%s", ip);
	verify_ip(ip);
    do
    {
        printf("\nentrer la masque de sous reseau = ");
        scanf("%s", mask);
        
        while(mask[i] != '\0')
        {
            if(mask[i] == '.')
            {
                n++;
            }
            i++;
        }
        if(n == 3)
        {
            sscanf(mask, "%d.%d.%d.%d" , &one,&two,&three,&four);
            strcat(chaine ,get_mask(b,one));
            strcat(chaine, get_mask(b,two));
            strcat(chaine , get_mask(b,three));
            strcat(chaine ,get_mask(b, four));
            ///printf(" ==> %s\n", b);
            char un[100] = {0};
            char nulo[100] = {0};
            
            if( (sscanf(b, "%32[^0]%32s", un, nulo) == 2))
            {
               /// printf("un =%s\n", un);
                ///printf("nulo = %s", nulo);
                i = 0;
                while(nulo[i] != '\0')
                {
                    if(nulo[i] == '1')
                    {
                        error = 1;
                    }
                    i++;
                }
            }
        } 
    }while(error != 0);
     
         
        address_reseau_broadcast(ip, mask);
        ///broadcast_address(ip,mask);
        nombre_machine(ip);
 }







    

    
