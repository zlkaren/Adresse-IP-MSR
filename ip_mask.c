#include <stdio.h>
#include <string.h>
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
    while(onebyte < 0 || onebyte > 255 ||  twobyte < 0 || twobyte > 255 || threebyte < 0 || threebyte > 255 ||  fourbyte < 0 || fourbyte > 255)
    {
        printf("veuillez entrer une adresse ip correcte = ");
        scanf("%s" , ip); 
    }
    return ip;
}

char* binaire(char* a, int f)
{
    int p = 0;
    int s = 0;

    for(int i = 7; i >= 0 ; i--)
    {
        p = pow(2, i);
        s = f - p;

        if(s >= 0)
        {
            f = s;
            strcat(a, "1");
        }
        else
        {
            strcat(a, "0");
        }
    }
    return a;
}

char* calcul_binaire(char * ip_binaire, char * mask_binaire, char * reseau)
{
    int i = 0;
    
    while(i < 32)
    {
        reseau[i] = ip_binaire[i] & mask_binaire[i]; 
        i++;
    }
    
    return reseau;
}

char* extraction_binary(char * decimal, char * chaine)
{
    chaine[0] = '\0';  /// Initialiser la chaine a vide
    int one = 0;
    int two = 0;
    int three = 0;
    int four = 0;
    
    char tmp_one[100] = {0};
    char tmp_two[100] = {0};
    char tmp_three[100] = {0};
    char tmp_four[100] = {0};
    
    sscanf(decimal, "%d.%d.%d.%d", &one, &two, &three, &four);
    
    strcat(chaine, binaire(tmp_one, one));
    strcat(chaine, binaire(tmp_two, two));
    strcat(chaine, binaire(tmp_three, three));
    strcat(chaine, binaire(tmp_four, four));

    return chaine;
}

char* to_decimal(char * binaire,char *decimal)
{
		char decimal_one[100] = {0};
		char decimal_two[100] = {0};
		char decimal_three[100] = {0};
		char decimal_four[100] = {0};
		int one = 0;
		int two = 0;
		int three = 0;
		int four = 0;
		
		///extraction  binaire 
		strncpy(decimal_one, binaire, 8);
		strncpy(decimal_two, binaire + 8, 8);
		strncpy(decimal_three, binaire + 16, 8);
		strncpy(decimal_four, binaire + 24, 8);

	///convertie le binaire en decimale
		for(int i = 0; i <8 ; i++)
		{
			if (decimal_one[i] == '1')
			{
				one += pow(2, 7 - i);
			}
		}
		for(int i = 0; i < 8; i++)
		{
			if (decimal_two[i] == '1')
			{
				two += pow(2, 7 - i);
			}
		}
		for(int i = 0; i < 8; i++)
		{
			if (decimal_three[i] == '1')
			{
				three += pow(2, 7 - i);
			}
		}
		for(int i = 0; i < 8; i++)
		{
			if (decimal_four[i] == '1')
			{
				four += pow(2, 7 - i);
			}
		}	
    
		sprintf(decimal , "%d.%d.%d.%d", one,two,three,four);
	
		return decimal;
}

int verify_mask(char * mask_binairy)
{
    char *tok = NULL;
    int error = 0;
    int i = 0;
    char ms[100] = {0};
    strcpy(ms, mask_binairy);
    
    tok = strtok(ms, "1");
    tok = strtok(NULL, " ");
    
    if (tok != NULL)
    {
        while(tok[i] != '\0')
        {
            if(tok[i] == '1')
            {
                error = 1;
                break;
            }
            i++;
        }
    }
    
    return error;
}


void broadcast(char* reseau_binairy, char* mask_binairy)
{
    int hote = 0;
    int i = 0;
    char ip_broadcast_decimal[100] = {0};
    char decimal[100] = {0};

    while(mask_binairy[i] != '\0')
    {
        if(mask_binairy[i] == '0')
        {
            hote++;
        }
        i++;
    }

    for(int j = 32 - hote; j < 32; j++)  
    {
        reseau_binairy[j] = '1'; 
    }
    strcat(ip_broadcast_decimal,to_decimal(reseau_binairy,decimal));
    printf("\nAdresse broadcast = %s", ip_broadcast_decimal);
    
}


void get_data_mask()
{
    char ip[100] = {0};
    char masque[100] = {0};
    char reseau[100] = {0};
    char ip_reseau_binaire[100] = {0};
    char decimal_reseau[100] = {0};
    char decimal[100] = {0};
    char mask_binairy[100] = {0};
    char ip_binairy[100] = {0};
    char tmp_binairy[100] = {0};
    char temp_binairy[100] = {0};
    int a;
    
    printf("entrer l'adresse ip de format (XXX.XXX.XXX.XXX) = ");
    scanf("%s", ip);
    verify_ip(ip);
    
    do
    {
        a = 0;
        mask_binairy[0] = '\0';  
        tmp_binairy[0] = '\0';   
    
        printf("Entrer le masque de sous reseau = ");
        scanf("%s", masque);
        
        strcat(mask_binairy, extraction_binary(masque, tmp_binairy));
        a = verify_mask(mask_binairy);
        
    } while(a != 0);
    strcat(ip_binairy, extraction_binary(ip, temp_binairy));
    strcat(ip_reseau_binaire,calcul_binaire(ip_binairy,mask_binairy,reseau));
    strcat(decimal_reseau,to_decimal(ip_reseau_binaire,decimal));
    printf("\t**********************");
    printf("\n\nAdresse reseau = %s", decimal_reseau);
    broadcast(ip_reseau_binaire, mask_binairy);
}
