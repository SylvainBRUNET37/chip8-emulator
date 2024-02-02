#include "./include/machine.h"
#include <dirent.h>
#include <string.h>

int main()
{
    struct t_machine* machine = initEmu();
    if (machine == NULL)
        return 1;

    unsigned short timerCounter = 0;
    int error = 0;
    while(1)
    {
        // Endort le programme pendant 2ms pour que le fetch/decode/execute se lance 500 fois par seconde (500Hz)
        SDL_Delay(2);
        error = fetchDecodeExecute(machine);
        if (error == 1)
        {
            printf("La valeur de x ou y donnee a la fonction de l'instruction n'est pas valide.\n");
            return 1;
        }
        else if (error == 2)
        {
            printf("L'instruction recuperee n'est pas valide.\n");
        }
            
        // Tous les 8 tours de boucle (fréquence : (500/8)Hz ~= 60Hz), décrémente les timers et met à jour l'affichage
        if (timerCounter == 1)
        {
            if (Display_update(machine->display) == 1)
            {
                printf("Une fonction de la librairie SDL n'a pas abouti.\n");
                return 1;
            }
            decrementTimer(machine->processor);
            timerCounter = 0;
        }
        timerCounter++;
    }
    SDL_Quit();
    return 0;
}

struct t_machine* initEmu()
{
    // Initialisation la vidéo et l'audio
    if((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)) 
    { 
        printf("Impossible d'initialiser la SDL : %s.\n", SDL_GetError());
        return NULL;
    }

    // Créé et initialise l'émulateur
    struct t_machine* machine = newMachine();
    if (machine == NULL)
    {
        printf("L'emulateur n'a pas pu etre cree/initialise.\n");
        return NULL;
    }
    
    // Initialise le compteur de programme
    machine->processor->programCounter = 512;
    
    // Demande à l'utilisateur quel ROM il veut lancer
    char* romPath = searchRomName();
    
    // Charge en RAM la ROM et les sprites représentatifs
    loadRepresentativeSprite(machine->RAM);
    loadRom(machine->RAM, romPath);

    return machine;
}

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
        // Boucle tant que le dossier n'a pas été lu en entier
        while ((file = readdir(directory)) != NULL)
        {
            // La fonction readdir lit ".." et "." : ne les stock pas si c'est le nom de fichier lu
            if (file->d_name[0] != '.')
            {
                romName[nbFile] = file->d_name;
                printf("%d : %s\n", (nbFile+1), file->d_name);
                nbFile++;
            }
        }
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


int initMachine(struct t_machine* machine)
{
    // Initialise la RAM
    machine->RAM = newRAM();
    if ((machine->RAM) == NULL)
        return 1;
    
    // Initialise le processeur
    machine->processor = newProcessor();
    if ((machine->processor) == NULL)
        return 1;

    // Alloue en mémoire le display, le speaker et le keyboard
    machine->display = malloc(sizeof(struct Display));
    machine->speaker = malloc(sizeof(struct Speaker));
    machine->keyboard = malloc(sizeof(struct Keyboard));

    // Initialise le display, le speaker et le keyboard
    if (Display_init(machine->display, 10) == 1)
        return 1;
        
    if (Speaker_init(machine->speaker) == 1)
    {
        printf("%s\n", SDL_GetError());
        return 1;
    }
        
    if (Keyboard_init(machine->keyboard) == 1)
        return 1;

    return 0;
}

void destroyMachine(struct t_machine* machine)
{
    if (machine != NULL)
    {
        // Détruit et libère le display
        Display_destroy(machine->display);
        free(machine->display);
        
        // Détruit et libère le display
        Speaker_destroy(machine->speaker);
        free(machine->speaker);
        
        // Détruit et libère le display
        Keyboard_destroy(machine->keyboard);
        free(machine->keyboard);

        // Détruit et libère le display
        deleteRAM(machine->RAM);
        free(machine->RAM);

        // Détruit et libère le processeur
        deleteProcessor(machine->processor);
        free(machine->processor);
    }
}

struct t_machine* newMachine()
{
    // Alloue en mémoire la structure
    struct t_machine* machine = malloc(sizeof(struct t_machine));
    if (machine == NULL)
        return NULL;
    // Initialise la structure
    if (initMachine(machine) == 1)
        return NULL;
    return machine;
}

void deleteMachine(struct t_machine* machine)
{
    // Désalloue la structure
    if (machine != NULL)
    {
        destroyMachine(machine);
        free(machine);
    }
}

void loadRepresentativeSprite(struct t_RAM* RAM)
{
    // Déclaration d'un tableau contenant les sprites représentatifs des chiffres hexadécimaux
    uint8_t representativeSprite[NB_REPRESENTATIVE_SPRITE] = 
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    
    // Écrit dans la RAM les réprésentation hexa des sprites dans les NB_REPRESENTATIVE_SPRITE premiers emplacements
    for (uint8_t i = 0 ; i < NB_REPRESENTATIVE_SPRITE ; i++)
        writeRAM(RAM, i, representativeSprite[i]);
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

int fetchDecodeExecute(struct t_machine* machine)
{
    // FETCH :
    // Récupère dans la RAM les 8 premiers bits de l'instruction
    uint16_t instruction = readRAM(machine->RAM, machine->processor->programCounter);
    // Décale les 8 bits récupéré vers la gauche
    instruction = instruction << 8;
    // Récupère dans la RAM les 8 derniers bits
    instruction += readRAM(machine->RAM, machine->processor->programCounter+1);
    
    // DECODE/EXECUTE : 
    // - les conditions dans les "if / else if" vérifient quel instruction a été récupérée en RAM
    // - les valeurs de x (et y) sont décalée de 8 (et 4) bits pour avoir leur valeur sur 4 bits
    if ((instruction & 0xFFFF) == 0x00E0)
    {
        CLS_00E0(machine->display);
    }
    else if ((instruction & 0xFFFF) == 0x00EE)
    {
        RET_00EE(machine->processor);
    }
    else if ((instruction & 0xF000) == 0x1000)
    {
        JP_1nnn(machine->processor, (instruction & 0x0FFF));
    }
    else if ((instruction & 0xF000) == 0x2000)
    {
        CALL_2nnn(machine->processor, (instruction & 0x0FFF));
    }
    else if ((instruction & 0xF000) == 0x3000)
    {
        if (SE_3xkk(machine->processor, (instruction & 0x0F00) >> 8, (uint8_t)(instruction & 0x00FF)) == 1)
            return 1;
    }
    else if ((instruction & 0xF000) == 0x4000)
    {
        if (SNE_4xkk(machine->processor, (instruction & 0x0F00) >> 8, (uint8_t)(instruction & 0x00FF)) == 1)
            return 1;
    }
    else if ((instruction & 0xF00F) == 0x5000)
    {
        if (SE_5xy0(machine->processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4) == 1)
            return 1;
    }
    else if ((instruction & 0xF000) == 0x6000)
    {
        if (LD_6xkk(machine->processor, (instruction & 0x0F00) >> 8, (u_int8_t)(instruction & 0x00FF)) == 1)
            return 1;
    }
    else if ((instruction & 0xF000) == 0x7000)
    {
        if (ADD_7xkk(machine->processor, (instruction & 0x0F00) >> 8, (uint8_t)(instruction & 0x00FF)) == 1)
            return 1;
    }
    else if ((instruction & 0xF00F) == 0x8000)
    {
        if (LD_8xy0(machine->processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4) == 1)
            return 1;   
    }
    else if ((instruction & 0xF00F )== 0x8001)
    {
        if (OR_8xy1(machine->processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4) == 1)
            return 1;
    }
    else if ((instruction & 0xF00F) == 0x8002)
    {
        if (AND_8xy2(machine->processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4) == 1)
            return 1;
    }
    else if ((instruction & 0xF00F) == 0x8003)
    {
        if (XOR_8xy3(machine->processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4) == 1)
            return 1;
    }
    else if ((instruction & 0xF00F) == 0x8004)
    {
        if (ADD_8xy4(machine->processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4) == 1)
            return 1;
    }
    else if ((instruction & 0xF00F) == 0x8005)
    {
        if (SUB_8xy5(machine->processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4) == 1)
            return 1;
    }
    else if ((instruction & 0xF00F) == 0x8006)
    {
        if (SHR_8xy6(machine->processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4) == 1)
            return 1;
    }   
    else if ((instruction & 0xF00F) == 0x8007)
    {
        if (SUBN_8xy7(machine->processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4) == 1)
            return 1;
    }
    else if ((instruction & 0xF00F) == 0x800E)
    {
        if (SHL_8xyE(machine->processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4) == 1)
            return 1;
    }
    else if ((instruction & 0xF00F) == 0x9000)
    {
        if (SNE_9xy0(machine->processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4) == 1)
            return 1;
    }
    else if ((instruction & 0xF000) == 0xA000)
    {
        LD_Annn(machine->processor, (instruction & 0x0FFF));
    }
    else if ((instruction  & 0xF000) == 0xB000)
    {
        JP_Bnnn(machine->processor, (instruction & 0x0FFF));
    }   
    else if ((instruction  & 0xF000) == 0xC000)
    {
        if (RND_Cxkk(machine->processor, (instruction & 0x0F00) >> 8, (uint8_t)(instruction & 0x00FF)) == 1)
            return 1;
    }
    else if ((instruction & 0xF000) == 0xD000)
    {
        if (DRW_Dxyn(machine->processor, machine->RAM, machine->display, (instruction  & 0x0F00) >> 8, (instruction & 0x00F0) >> 4, (instruction & 0x000F)) == 1)
            return 1;
    }
    else if ((instruction & 0xF0FF) == 0xE09E)
    {
        if (SKP_Ex9E(machine->processor, machine->keyboard, (instruction & 0x0F00) >> 8) == 1)
            return 1;
    }
    else if ((instruction & 0xF0FF) == 0xE0A1)
    {
        if (SKNP_ExA1(machine->processor, machine->keyboard, (instruction & 0x0F00) >> 8) == 1)
            return 1;
    }
    else if ((instruction & 0xF0FF) == 0xF007)
    {
        if (LD_Fx07(machine->processor, (instruction & 0x0F00) >> 8) == 1)
            return 1;
    }
    else if ((instruction & 0xF0FF) == 0xF00A)
    {
        if (LD_Fx0A(machine->processor, machine->keyboard, (instruction & 0x0F00) >> 8) == 1)
            return 1;
    }
    else if ((instruction & 0xF0FF) == 0xF015)
    {
        if (LD_Fx15(machine->processor, (instruction & 0x0F00 ) >> 8) == 1)
            return 1;
    }
    else if ((instruction & 0xF0FF) == 0xF018)
    {
        if (LD_Fx18(machine->processor, (instruction & 0x0F00) >> 8) == 1)
            return 1;
    }
    else if ((instruction & 0xF0FF) == 0xF01E)
    {
        if (ADD_Fx1E(machine->processor, (instruction & 0x0F00) >> 8) == 1)
            return 1;
    }
    else if ((instruction & 0xF0FF )== 0xF029)
    {
        if (LD_Fx29(machine->processor, (instruction & 0x0F00) >> 8) == 1)
            return 1;
    }
    else if ((instruction & 0xF0FF) == 0xF033)
    {
        if (LD_Fx33(machine->processor, machine->RAM, (instruction & 0x0F00) >> 8) == 1)
            return 1;
    }
    else if ((instruction & 0xF0FF) == 0xF055)
    {
        if (LD_Fx55(machine->processor, machine->RAM, (instruction & 0x0F00) >> 8) == 1)
            return 1;
    }
    else if ((instruction & 0xF0FF) == 0xF065)
    {
        if (LD_Fx65(machine->processor, machine->RAM, (instruction & 0x0F00) >> 8) == 1)
            return 1;
    }
    else
    {
        printf("Inctruction : %x\n", instruction);
        return 2;
    }

    // Incrémente le compteur de programme
    machine->processor->programCounter += 2;
    return 0;
}