// Teile des Codes kommen aus dem Netz und ich denke, es ist besser, hier was dazu reinzutun

//**************************************
// Name: Directory Listing for Windows
// Description:Displays a list of files
//     and subdirectories in a directory.
// By: koby-GR
//This code is copyrighted and has
// limited warranties.Please see
//http://www.Planet-Source-Code.com/vb...=6790&lngWId=3
//for details.
//**************************************
/* Directory Listing for Windows by koby
*http://www.codecraft.tk
*
* Displays a list of files and subdirectories in a directory.
* Usage : ls [drive:][path] Specifies drive and/or directory to list.
* Copyright (c) 2003
* koby and www.CodeCraft.tk. All rigths reserved
* Redistributions of source code must retain the above copyright
* notice and the following disclaimer.
*
* this SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
*ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS for A PARTICULAR PURPOSE
*ARE DISCLAIMED.
*/

//ein Vokabeltrainer

//Include der nötigen Dateien

#include <iostream> //Allgemeine Funktionen à la std::cout
#include <string> //Für Strings
#include <time.h> //Für die rand() funktion
#include <fstream> //für's Datei Einlesen

#include <stdio.h> //Für's Ordner auslesen
#include <windows.h> // - " -

// V A R I A B L E N

//Anzahl der Vokabeln
int vok_gesamt = 0;
int vok_aktuell = 0;
int vok_gefragt[128];
std::string datei_name[64];

//Erstellen der Struct für die Vokabeln
struct vokabel
{
    //die Vokabel auf Deutsch
    std::string deutsch[8];
    //die Vokabel auf Latein
    std::string latein;
    //Anzahl an deutschen übersetzungen
    int num;
};

// F U N K T I O N E N

bool isunused(int num)
{
    for(int i=0;i<vok_aktuell;i++)
    {
        if(vok_gefragt[i]==num)
            return (0);
    }
    return(1);
}

//Ordner Auslese Funktion

int ls(char *path) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char VolumeName[MAX_PATH], FileSys[5];
	//int VolSerNum;
	//GetVolumeInformation(NULL, VolumeName, MAX_PATH, &VolSerNum, NULL, NULL, FileSys, 5);
	//printf(" Volume in drive %c is %s\n", 64+getdrive(), VolumeName);
	//printf(" File System is %s\n", FileSys);
	//printf("\n Directory of %s\n\n", path);
	strcat(path, "\\*");
	hFind=FindFirstFile(path, &FindFileData);
	int tempint=1;
	do
	{
//	    if(FindFileData.cFileName!=".."&&FindFileData.cFileName!=".")
//		printf("%*s", 30, FindFileData.cFileName);
/*        if(test<2) //Die ersten beiden (.. und .) werden nicht ausgegeben
            test++;
        else*/
        if( FindFileData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY &&
         FindFileData.dwFileAttributes != FILE_ATTRIBUTE_SYSTEM &&
         FindFileData.dwFileAttributes != FILE_ATTRIBUTE_ENCRYPTED &&
         FindFileData.dwFileAttributes != FILE_ATTRIBUTE_HIDDEN &&
         FindFileData.dwFileAttributes != FILE_ATTRIBUTE_COMPRESSED)
         {
            std::cout<<tempint<<") "<<FindFileData.cFileName<<"\n";
            datei_name[tempint]=FindFileData.cFileName;
            tempint++;
         }
/*		if( FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY )
			printf("\t<DIR>");
		if( FindFileData.dwFileAttributes == FILE_ATTRIBUTE_HIDDEN )
			printf("\t<Hidden>");
		if( FindFileData.dwFileAttributes == FILE_ATTRIBUTE_COMPRESSED )
 			printf("\t<Compressed>");
 		if( FindFileData.dwFileAttributes == FILE_ATTRIBUTE_SYSTEM )
  			printf("\t<System>");
  		if( FindFileData.dwFileAttributes == FILE_ATTRIBUTE_ENCRYPTED )
  			printf("\t<Encrypted>\n");
   		else*/
   			//printf("\n");
    } while ( FindNextFile(hFind, &FindFileData) && tempint<64);
    FindClose(hFind);
    return (tempint);
}

// M A I N

//Die Main Funktion
int main (int argc, char *argv[])
{
    vokabel vokabeln[128]; //vokabel-struct für die Vokabeln

    //Code um Dateien im Ordner auszugeben
    char path[MAX_PATH];
    if(argc==2)
    {
        strcpy(path, argv[1]);
    }
    else
    {
    	GetCurrentDirectory(MAX_PATH, path);
    }
    std::cout<<"Bitte gib die Nummer der Datei, die geladen werden soll, ein.\nListe der Dateien:\n";
    int tempint=ls(path);
    std::cout<<"\nEingabe:";

    int eingabe=1;
    //std::cout<<tempint;
    do
    {
        std::cin>>eingabe;
    } while (eingabe<1||eingabe>tempint);

    //Irgendwie muss der string-array datei_name zum char gemacht werden, damit ifstream.open ordentlich funktioniert
    //char datei_name_char[128];

    //datei_name_char=datei_name[eingabe].c_str();

/*    std::strncpy(datei_name_char, datei_name[eingabe], sizeof(datei_name[eingabe]) - 1);
    datei_name_char[sizeof(datei_name_char) - 1] = '\0';

    std::cout<<datei_name[eingabe]<<"\n"<<datei_name_char;
*/
    //Datei laden
    std::ifstream infile;
    infile.open (datei_name[eingabe].c_str(), std::ifstream::in); //Öffnen der Datei
    std::string tempchar; //Char für's aktuelle Zeichen
    std::string tempstring; //String für's aktuelle Wort

    bool tempbool=true; //Bool, wird für die vok_gesamt anzahl gebraucht
    vokabeln[0].num=1; //Das geht in der while schleife nicht (so leicht)
    while(infile.good())
    {
        tempchar = (char)infile.get(); //Buchstabe auslesen
        if(tempchar=="="||tempchar==";") //Trennzeichen für die Wörter
        {
            //std::cout<<"Tempchar ist "<<tempchar<<"\n";
            tempbool = !tempbool; //Jedes 2. mal wird eine deutsche vokabel hinzugefügt
            if(tempbool)
            {
                vok_gesamt++;
                vokabeln[vok_aktuell].deutsch[vokabeln[vok_aktuell].num-1] = tempstring;
                //std::cout<<"Es wurde hinzugefuegt: "<<vok_aktuell<<". deutsch: "<<tempstring<<"\n";
                vok_aktuell++;
                vokabeln[vok_aktuell].num=1;

            }
            else
            {
                vokabeln[vok_aktuell].latein=tempstring;
                //std::cout<<"Es wurde hinzugefuegt: "<<vok_aktuell<<". lateinisch: "<<tempstring<<"\n";
            }
            tempstring="";
        }
        //Wenn . zwischen 2 deutschen wörtern steht, gibt es mehrere Übersetzungen
        else if (tempchar=="."&&!tempbool&&vokabeln[vok_aktuell].num<=8)
        {
            //std::cout<<"\n"<<"Tempchar ist \".\", vokabeln[vok_aktuell].num ist  "<<vokabeln[vok_aktuell].num<<"."<<"\n";
            vokabeln[vok_aktuell].deutsch[vokabeln[vok_aktuell].num-1] = tempstring;
            vokabeln[vok_aktuell].num++;
            tempstring="";

        }
        else
        {
            tempstring+=tempchar;
            //std::cout<<"tempstring: "<<tempstring<<" tempchar:"<<tempchar<<"\n";
        }
    }
    infile.close();

    vok_aktuell = 0; //vok_aktuell wurde vorhin für
    //Vokabeln
/*
    vokabeln[0].deutsch="Herr";
    vokabeln[0].latein="dominus";
    vokabeln[1].deutsch="Herrin";
    vokabeln[1].latein="domina";
    vokabeln[2].deutsch="Sklave";
    vokabeln[2].latein="servus";*/

    //vorbeireiten der rand funktion
    srand( (unsigned)time( NULL ) );

    //zufällige Variable
    int random=rand()%vok_gesamt;

    //Int für die richtigen Übersetzungen
    int richtig=0;

    //die Variable für die Antwort des Spielers
    //Früher String, jetzt Char Array
    //std::string antwort;
    char antwort[128];

    //Spielregeln
    std::cout<<"Los gehts! Es gibt "<<vok_gesamt<<" Vokabeln.\n";

    //Die Spielschleife
    for(int i=0;i<vok_gesamt;i++)
    {
        //Es wird eine zufällige Zahl zwischen 0 und der zahl an vokabeln - 1 errechnet
        while(!isunused(random))
            random=rand()%vok_gesamt;
        vok_gefragt[i]=random;

        //Vokabel abfagen
        std::cout<<"Uebersetze: "<<vokabeln[random].latein<<"\n";

        //Statt cin verwende ich jetzt fgets, damit auch Leerzeichen verwendet werden können.
        //std::cin>>antwort;
        do
        {
        std::fflush(stdin);
        std::fgets(antwort, 100, stdin);
        }while(strlen(antwort)==1);

        //Am Ende steht noch ein newline, das muss weg.
        antwort[strlen(antwort)-1]='\0';


        if(antwort==vokabeln[random].deutsch[0]||
        antwort==vokabeln[random].deutsch[1]||
        antwort==vokabeln[random].deutsch[2]||
        antwort==vokabeln[random].deutsch[3]||
        antwort==vokabeln[random].deutsch[4]||
        antwort==vokabeln[random].deutsch[5]||
        antwort==vokabeln[random].deutsch[6]||
        antwort==vokabeln[random].deutsch[7])
        {
            std::cout<<"Richtig!\n";
            richtig++;
            if(vokabeln[random].num>1) //Wenn es mehrere richtige Lösungen gibt, liste sie auf.
            {
                std::cout<<vokabeln[random].latein<<" hat die Uebersetzungen\n";
                for(int i=0;i<8;i++)
                {
                    if(vokabeln[random].deutsch[i]!="")
                        std::cout<<vokabeln[random].deutsch[i]<<"\n";
                }
            }
        }
        else
        {
            std::cout<<"\aFalsch!\n";

            std::cout<<vokabeln[random].latein<<" hat die Uebersetzung";
            if(vokabeln[random].num>1)
                std::cout<<"en";
            std::cout<<"\n";
            for(int i=0;i<vokabeln[random].num;i++)
            {
                std::cout<<vokabeln[random].deutsch[i]<<"\n";
            }
        }

        vok_aktuell++;
    }

    //Beliebige Taste zum Beenden
    std::cout<<"\nDu hast "<<richtig<<" von "<<vok_gesamt<<" Vokabeln richtig uebersetzt. Das sind "<<((double)richtig/(double)vok_gesamt)*100<<"%.\n";
    std::cout<<"\nZum Beenden Enter druecken.\n";
    std::fflush(stdin);
    std::getchar();

    return(0);
}
