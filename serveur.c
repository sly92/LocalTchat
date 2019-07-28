#include <stdio.h>      //printf
#include <string.h>    //strlen
#include <stdlib.h>    //bind
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
 

/** Programme principal **/

int main(int argc , char *argv[])
{

    int socket_serveur;
    int nouvelle_socket;
    int taille_socket;

    struct sockaddr_in serveur;
    struct sockaddr_in client;

      
    int read_size;
    char client_message[2000];
    

    //Creation du socket
    socket_serveur = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_serveur == -1)
    {
        printf("Erreur lors de la creation du socket");
    }

    //Prepare la structure sockaddr_in 
    serveur.sin_family = AF_INET;
    serveur.sin_addr.s_addr = INADDR_ANY;
    serveur.sin_port = htons( 8888 );

    //Liaison des clients au serveurs
    if( bind(socket_serveur,(struct sockaddr *)&serveur , sizeof(serveur)) < 0)
    {
        printf("liaison echoué");
        return 1;
    }
    printf("liaison établis");

    printf("En attente de connexion entrante");

    //Ecoute les connexions entrantes
    listen(socket_serveur , 3);

    
    taille_socket = sizeof(struct sockaddr_in);

    //Accepte les connexions entrantes
    if( (nouvelle_socket = accept(socket_serveur, (struct sockaddr *)&client, (socklen_t*)&taille_socket)) )
    {
        printf("Connexion accepté");

        write(socket_serveur , "Vous pouvez commencer à discuter", strlen("Vous pouvez commencer à discuter"));

            //Recois un message du client
            while( (read_size = recv(socket_serveur , client_message , 2000 , 0)) > 0 )
            {
                // Renvois ce message au client
                write(socket_serveur , client_message , strlen(client_message));
            }

    }

    if (nouvelle_socket<0)
    {
        printf("Aucune connexion accepté");
        return 1;
    }

    close(nouvelle_socket);
    close(socket_serveur);
    return 0;
}

