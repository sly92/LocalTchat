#include <stdio.h> //printf
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr


/** Programme principal **/

int main(int argc , char *argv[])   
{
    int sock;                   // Declaration socket du coté client
    struct sockaddr_in client;     // Creation structure sin de type sockaddr_in (information technique du socket coté client)
    char message_client[2000];         // Creation tableau char pour message et reponse serveur
    char reponse_serveur[2000];    

     //  *** Creation du socket ***
    sock = socket(AF_INET , SOCK_STREAM , 0);   // Creation du socket (Famille du socket, Type du socket, Protocole)

    if (sock == -1)
    {
        printf("Erreur de creation socket");    
    }
   
    printf("Creation du socket");

    client.sin_addr.s_addr = inet_addr("192.168.0.31");    // Adresse IP du serveur
    client.sin_family = AF_INET;                        // Famille du socket 
    client.sin_port = htons( 8888 );                    // Port d'ecoute 

    //Connexion serveur
    if (connect(sock , (struct sockaddr *)&client , sizeof(client)) < 0) // Connexion 
    {
        printf("Connexion échoué, Erreur");   
        return 1;
    }

    printf("Connexion réussi\n");
    printf("Bienvenue dans LocalChat");

    // Garder la connexion au serveur
    while(1)
    {

        printf("Entrer votre message: ");
        fgets(message_client, sizeof(message_client),stdin);

        //Envoyer
        if( send(sock , message_client , strlen(message_client) , 0) < 0)
        {
            printf("Echec de l'envois du message");
            return 1;
        }

        //Recevoir reponse du serveur
        if( recv(sock , reponse_serveur , 2000 , 0) < 0)
        {
            printf("Echec de la reponse du serveur");
            break;
        }

    printf("Reponse du serveur: %s\n", reponse_serveur);
    reponse_serveur[0]='\0';                            // vide le tableau de caractère reponse_serveur[]
    write(sock , reponse_serveur , strlen(reponse_serveur));    // reponsable connexion, texte, taille du texte
    }

    close(sock);    //ferme le socket
    return 0;
}



/* Pour le Tchat multi clients */

/* Utilisez une liste "client connecté", 
   protégé par verouillage mutex. 
   Quand un client se connecte au serveur de messagerie il faut l'ajouter connects, s'il se deconnecte le supprimer de la liste.
   Quand un client envois un message utiliser le verouilage de la liste "client connecté" et la parcourir pour renvoyer le message a tous les clients connectés. 
*/
