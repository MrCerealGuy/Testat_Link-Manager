/* Andreas Zahnleiter,  Matr.-Nr 0222480,  Sem. 1Nb */

/*
   Testataufgabe: Link-Manager Version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Makro
#define PRESS_ANY_KEY() fflush(stdin); getchar(); clr_screen()

// Menü-Punkte
enum MENUE_POINT {MENUE_SHOW = 1, MENUE_ADD, MENUE_DEL, MENUE_DELALL, MENUE_EXIT};

// Funktions-Prototypen
void draw_title(void);          /* Zeichnet den Titel auf den Bildschirm */
void clr_screen(void);          /* Löscht den Bildschirminhalt           */
void draw_menue(void);          /* Zeichnet das Menü auf den Bildschirm  */
int  menue_sel(void);           /* Menü-Auswahl - gibt Menüpunkt zurück  */
void draw_msg(char msg[76]);    /* Zeigt Status-Meldungen an             */
void error_msg(char msg[76]);   /* Zeigt Fehlermeldungen an              */

void menue_showlinks();         /* Alle Links anzeigen                   */
void menue_addlink();           /* Link hinzufügen                       */
void menue_dellink();           /* Link löschen                          */
void menue_delall();            /* Alle Links löschen                    */
void show_number_of_links();    /* Zeigt die Anzahl der Links an         */

// Globale Variablen
char  url[5][128+1];            /* URL - Array                           */
char desc[5][128+1];            /* URL-Beschreibung - Array              */
int  n_link = 0;                /* Anzahl gespeicherter Links            */

int main()
{		
	int error = 0;    /* Fehler - Flag           */
	int sel;          /* Menü-Auswahl            */
	int no_exit = 1;  /* Programm beenden - Flag */

	do  /* Programm-Schleife */
	{
		do  /* Menü-Schleife */
		{
			draw_title();
			draw_menue();

			if ((sel = menue_sel()) == -1) 
				error = 1; 
			else 
				error = 0;
	
		} while (error);

		/* Menü Punkt auswerten */
		switch (sel)
		{
			case MENUE_SHOW:   /* Alle Links anzeigen */
				menue_showlinks();
			break;

			case MENUE_ADD:    /* Link hinzufügen     */
				menue_addlink();
			break;

			case MENUE_DEL:    /* Link löschen        */
				menue_dellink();
			break;

			case MENUE_DELALL: /* Alle Links löschen  */
				menue_delall();
			break;

			case MENUE_EXIT:   /* Programm beenden    */
				no_exit = 0;
				draw_msg("Programm beendet...");
			break;
		}

	} while (no_exit);

	return 0;  /* Programm Ende */
}

void draw_title(void)
{
	int i;

	for (i = 1, putchar(218); i <= 78; i++) putchar(196); putchar(191);
	printf("%c%27cLink-Manager Version 1.0%27c%c", 179, ' ', ' ', 179);
	printf("%c%78c%c", 179, ' ', 179);
	printf("%c%19cvon Andreas Zahnleiter, Matr.-Nr. 0222480%18c%c", 179, ' ', ' ', 179);
	for (i = 1, putchar(192); i <= 78; i++) putchar(196); printf("%c\n\n",217);
}

void clr_screen(void)
{
	system("cmd.exe /C \"cls\"");  /* Ruft den internen DOS-Befehl 'cls' auf */
}

void draw_menue(void)
{
	printf("Alle Links anzeigen   [1]\n");  /* MENUE_SHOW   = 1 */
	printf("Link hinzufuegen      [2]\n");  /* MENUE_ADD    = 2 */
	printf("Link loeschen         [3]\n");  /* MENUE_DEL    = 3 */
	printf("Alle Links loeschen   [4]\n");  /* MENUE_DELALL = 4 */
	printf("Programm beenden      [5]\n");  /* MENUE_EXIT   = 5 */
}

int menue_sel(void)
{
	int a;

	printf("\n\nAuswahl: ");
	scanf("%d",&a);
	
	if (a < MENUE_SHOW || a > MENUE_EXIT)
	{
		error_msg("Ungueltige Eingabe! Bitte eine Taste druecken!");
		return -1;
	}

	return a;
}

void draw_msg(char msg[76])
{
	int i, msg_len, a;

	msg_len = strlen(msg);

	printf("\n\n\n");

	for (i = 1, putchar(218); i <= 78; i++) putchar(196); putchar(191);

	a = (77 - msg_len);

	printf("%c %s", 179, msg);
	for (i = 1; i <= a; i++) putchar(' ');
	putchar(179);

	for (i = 1, putchar(192); i <= 78; i++) putchar(196); putchar(217);
}

void show_number_of_links()
{
	printf("\n%d Link(s) in der Top5-Liste",n_link);
	PRESS_ANY_KEY();
}

void menue_showlinks()
{
	int i;

	if (n_link == 0)  /* Liste leer ? */
	{
		error_msg("Top5-Liste ist leer! Bitte eine Taste druecken!");
		return;
	}

	clr_screen();

	/* Alle URLs mit Beschreibungen anzeigen */
	for (i = 0; i != n_link; i++)
	{
		printf("\n[%d]",i);
		printf("\nURL         : %s", url[i]);
		printf("\nBeschreibung: %s\n", desc[i]);
	}

	PRESS_ANY_KEY();
}

void menue_addlink()
{
	char  s_url[128+1];
	char s_desc[128+1];
	int i;

	if (n_link == 5)  /* Liste voll ? */
	{
		error_msg("Top5-Liste voll! Bitte eine Taste druecken!");
		return;
	}

	/* URL eingeben */
	printf("\nURL         : ");
	scanf("%s",s_url);

	/* Prüfe, ob URL schon vorhanden ist */
	for (i = 0; i != n_link; i++)
	{
		if (strcmp(url[i], s_url) == 0)
		{
			error_msg("Link schon vorhanden! Bitte eine Taste druecken!");
			return;
		}
	}

	/* Beschreibung eingeben */
	printf("Beschreibung: ");
	fflush(stdin);
	gets(s_desc);

	/* Okay, URL und Beschreibung in Liste aufnehemen */
	strcpy(url[n_link], s_url);
	strcpy(desc[n_link], s_desc);

	n_link++;

	show_number_of_links();
}

void menue_dellink()
{
	int index, i, j;

	char  _url[5][128+1];  /* Hilfs-Array für die URLs           */
	char _desc[5][128+1];  /* Hilfs-Array für die Beschreibungen */
	char msg[128];

	if (n_link == 0)  /* Liste leer ? */
	{
		error_msg("Top5-Liste ist leer! Bitte eine Taste druecken!");
		return;
	}

	printf("\nBitte Index angeben: ");
	scanf("%d",&index);

	/* Prüfe, ob der Index gültig ist */
	if (index > (n_link - 1))
	{
		error_msg("Eintrag existiert nicht! Bitte eine Taste druecken!");
		return;
	}

	/* Kopiere alle Einträge außer den zu löschenden Eintrag in ein Hilfs-Array */
	for (i = 0, j = 0; i != n_link; j++)
	{
		if (j != index)
		{
			strcpy(_url[i], url[j]);
			strcpy(_desc[i], desc[j]);
			i++;
		}
	}

	n_link--;

	/* Kopiere nun das gesamte Hilfs-Array in das ursprüngliche Array zurück */
	for (i = 0; i < n_link; i++)
	{
		strcpy(url[i], _url[i]);
		strcpy(desc[i], _desc[i]);
	}
	
	sprintf(msg, "Link [%d] geloescht! Bitte eine Taste druecken!", index);
	draw_msg(msg);
	PRESS_ANY_KEY();
}

void menue_delall()
{
	if (n_link == 0)  /* Liste leer ? */
	{
		error_msg("Top5-Liste ist leer! Bitte eine Taste druecken!");
		return;
	}

	n_link = 0;

	draw_msg("Top5-Liste geloescht! Bitte eine Taste druecken!");
	PRESS_ANY_KEY();
}

void error_msg(char msg[76])
{
	putchar('\a');  /* Pieps-Ton, signalisiert Fehlermeldung */
	draw_msg(msg);  
	PRESS_ANY_KEY();
}