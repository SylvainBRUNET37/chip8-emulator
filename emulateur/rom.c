/**
 * \file  rom.h
 * \brief 
 */

#include <dirent.h>
#include <string.h>

#include "./include/rom.h"

char* searchRomName()
{
    struct dirent* file;
    char* romName[50];
    
    // Ouvre le répertoir de ROM
    DIR* directory = opendir("./rom"); 
    if (directory)
    {
        unsigned int nbFile = 0;
        printf("ROM disponibles :\n");
        printf("***************************************************\n");
        // Boucle tant que le dossier n'a pas été lu en entier
        while ((file = readdir(directory)) != NULL)
        {
            // La fonction readdir lit ".." et "." ; ne les stock pas si c'est le nom de fichier lu
            if (file->d_name[0] != '.')
            {
                romName[nbFile] = file->d_name;
                printf("%d : %s\n", (nbFile+1), file->d_name);
                nbFile++;
            }
        }
        printf("***************************************************\n");
        // Ferme le repértoire puis demande à l'utilisateur quel ROM il veut lancer
        closedir(directory);
        return askRom(romName, nbFile);
    }
    // Affiche un message d'erreur si le répertoire n'a pas pu être ouvert
    else
    {
        printf("Le repertoire de ROM n'a pas pu etre ouvert.\n");
        return "";
    }

}

char* askRom(char* romName[50], unsigned int nbFile)
{
    unsigned int romNumber = 0;
    char romPath[150];
    // Initialiser le début du chemin
    strcpy(romPath, "./rom/");
    
    // Demande à l'utilisateur le numéro de la ROM qu'il veut lancer
    do
    {
        printf("Saisissez le numero de la rom que vous voulez lancer : ");
        scanf("%u", &romNumber);
    } while (romNumber < 1 || romNumber > nbFile);

    // Concatene le début du chemin (./rom/) avec le nom de la ROM
    strncat(romPath, romName[romNumber-1], sizeof(romPath)-strlen(romPath)-1);

    // Retourner une copie allouée dynamiquement
    return strdup(romPath);
}

void loadRom(struct t_RAM* RAM, char* romPath)
{
    FILE* file;
    uint8_t value;
    u_int16_t i = 0;
    
    // Ouvre la ROM
    file = fopen(romPath, "rb");
    
    // Charge la ROM dans la RAM à partir de l'adresse 512 (tant que le fichier n'est pas fini)
    while (fread(&value, sizeof(uint8_t), 1, file))
    {
        writeRAM(RAM, (512+i), value);
        i++;
    }
}