/* Andreas Zahnleiter,  Matr.-Nr 0222480,  Sem. 1Nb 

   Testataufgabe: Link-Manager Version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRESS_ANY_KEY() fflush(stdin); getchar(); clr_screen()

char  url[5][128+1];            /* URL - Array                 */
char desc[5][128+1];            /* URL-Beschreibung - Array    */
int  n_link = 0;                /* Anzahl gespeicherter Links  */

void clr_screen(void) { system("cls"); }

void draw_msg(char msg[256])
{
	printf("\n\n%s",msg); PRESS_ANY_KEY();
}

int menue_sel(void)
{
	int a;

	printf("\n\nAuswahl: ");
	scanf("%d",&a);
	
	if (a < 1 || a > 5)
	{
		draw_msg("\aUngueltige Eingabe! Bitte eine Taste druecken!");
		return -1;
	}

	return a;
}

void show_number_of_links()
{
	printf("\n%d Link(s) in der Top5-Liste",n_link);
	PRESS_ANY_KEY();
}

void menue_showlinks()
{
	int i;

	if (n_link == 0)
		draw_msg("\aTop5-Liste ist leer! Bitte eine Taste druecken!");
	else
	{
		for (i = 0, clr_screen(); i != n_link; i++)
		{
			printf("\n[%d]",i);
			printf("\nURL         : %s", url[i]);
			printf("\nBeschreibung: %s\n", desc[i]);
		}

		PRESS_ANY_KEY();
	}
}

void menue_addlink()
{
	char  s_url[128+1];

	if (n_link == 5)
		draw_msg("\aTop5-Liste voll! Bitte eine Taste druecken!");
	else
	{
		printf("\nURL         : ");
		scanf("%s",s_url);

		printf("Beschreibung: ");
		fflush(stdin); gets(desc[n_link]);

		strcpy(url[n_link++], s_url);
		show_number_of_links();
	}
}

void menue_dellink()
{
	int i, index;
	char msg[128];

	if (n_link == 0)
		draw_msg("\aTop5-Liste ist leer! Bitte eine Taste druecken!");
	else
	{
		printf("\nBitte Index angeben: ");
		scanf("%d",&index);

		if (index < 0 || index > (n_link - 1))		
			draw_msg("\aEintrag existiert nicht! Bitte eine Taste druecken!");
		else
		{
			for (i = index; i < n_link; i++)
			{
				strcpy(url[i],url[i+1]);
				strcpy(desc[i],desc[i+1]);
			}
			n_link--;

			sprintf(msg, "Link [%d] geloescht! Bitte eine Taste druecken!", index);
			draw_msg(msg);
		}
	}
}

void menue_delall()
{
	if (n_link == 0)
		draw_msg("\aTop5-Liste ist leer! Bitte eine Taste druecken!");
	else
	{
		n_link = 0;
		draw_msg("Top5-Liste geloescht! Bitte eine Taste druecken!");
	}
}

main()
{		
	int error = 0, no_exit = 1, sel;  

	do  /* Programm-Schleife */
	{
		do  /* Menü-Schleife */
		{
			printf("%28cLink-Manager Version 1.0%28c", ' ', ' ');
			printf("%20cvon Andreas Zahnleiter, Matr.-Nr. 0222480%19c\n\n\n", ' ', ' ');

			printf("Alle Links anzeigen   [1]\n");  
			printf("Link hinzufuegen      [2]\n");  
			printf("Link loeschen         [3]\n");  
			printf("Alle Links loeschen   [4]\n");  
			printf("Programm beenden      [5]\n");

			error = ((sel = menue_sel()) == -1) ? 1 : 0;
	
		} while (error);

		switch (sel)
		{
			case 1: menue_showlinks(); break;
			case 2: menue_addlink();   break;
			case 3: menue_dellink();   break;
			case 4: menue_delall();    break;
			case 5:  
				no_exit = 0; draw_msg("Programm beendet...");
			break;
		}

	} while (no_exit);
}