#include "server.h"
#include "SimpleList.h"

/* A simple server in the internet domain using TCP
   The port number is passed as an argument */

/*STATIC VARIABLES*/
SimpleList  * sl;
int thread_exit;
int server_sock;


void sigHandler(int dummy) 
{
	thread_exit = TRUE;
	shutdown(server_sock,SHUT_RDWR);
	close(server_sock);
	printf("\n[-] Closing Server\n");
}

void * sessionAcceptor( void * args)
{

	server_sock = 0;													 	// file descriptor for our server socket
	int newsockfd = 0;												  // file descriptor for a client socket
	socklen_t clilen = 0;											 // utility variable - size of clientAddressInfo below
	int n = -1;												    		// utility variable - for checking pthread_create return vals
	struct sockaddr_in serverAddressInfo;				     // Super-special secret C struct that holds address info for building our server socket
	struct sockaddr_in clientAddressInfo;					 // Super-special secret C struct that holds address info about our client socket
	int i = 0; 													   // looping variable
	int sl_size = 0;											  // variable used to store size of simple list	
   int iSetOption = 1;										 // variable used to set socket options

   //pthread_t id = pthread_self();
   //printf("[-] Session acceptor running with thread id %lu \n",(unsigned long)id);

   thread_exit = 0;
   server_sock = socket(AF_INET, SOCK_STREAM, 0);

   if (server_sock < 0)
   {
   	error("ERROR opening socket");
   }

   n = setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption, sizeof(iSetOption));

   if (n != 0) 
   {
   	error("[-] ERROR creating socket");
   }

	// zero out the socket address info struct .. always initialize!
   bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));

	// set the remote port .. translate from a 'normal' int to a super-special 'network-port-int'
   serverAddressInfo.sin_port = htons(PORT);

	// set a flag to indicate the type of network address we'll be using  
   serverAddressInfo.sin_family = AF_INET;

	// set a flag to indicate the type of network address we'll be willing to accept connections from
   serverAddressInfo.sin_addr.s_addr = INADDR_ANY;

	/** We have an address struct and a socket .. time to build up the server socket **/

	// bind the server socket to a specific local port, so the client has a target to connect to      
   if (bind(server_sock, (struct sockaddr *) &serverAddressInfo, sizeof(serverAddressInfo)) < 0)
   {
   	printf("[-] ERROR on binding");

   }


	// set up the server socket to listen for client connections
   listen(server_sock,5);

   clilen = sizeof(clientAddressInfo);


   while (thread_exit != TRUE)
   {
   	
   	newsockfd = accept(server_sock, (struct sockaddr *) &clientAddressInfo, &clilen);
   	if(thread_exit == TRUE)
   	{
   		break;
   	}
   	pthread_t client_thread;

   	if (newsockfd < 0) 
   	{
   		error("[-] ERROR on accept");
   	}

		n = pthread_create(&(client_thread), NULL, &connectionHandler, (void *) &newsockfd); //add pthread id to linked list


		if (n != 0)
		{
			close(server_sock);
			error("\n[-]can't create thread :[]\n"); 
		}

	}

	//sig int has been called. time to join threads created
	sl_size = getSize(sl);

	for(i = 0; i < sl_size; i++)
	{
		pthread_t temp = getFront(sl);
		pthread_join(temp, NULL);
	}

	return 0;

}

/*This handles client connection && sets up the actual 'server'*/
void * connectionHandler( void * client_socket)
{

	printf("Connection made");
	int socket = *(int *)client_socket; 
	char buffer[BUFFER_SIZE];									  // char array to store data going to and coming from the socket
	int closeWithoutMessage = FALSE;							 // int used to determine error message to send to client
	int n = 0;														// utitlity var used for read and write value
	
	char * returnMessage = "Success";
	//pthread_t id = pthread_self();
	//printf("[-]connection handler running with thread id %lu \n",(unsigned long)id);

	while(thread_exit != TRUE) 
	{
		bzero(buffer,BUFFER_SIZE);

		n = write(socket,returnMessage,BUFFER_SIZE);

		if (n < 0)
		{
			printf("[-] ERROR writing to the socket\n");
			closeWithoutMessage = TRUE;
			break;
		}

		// try to read from the client socket
		n = read(socket,buffer,BUFFER_SIZE -1);
		if(thread_exit == TRUE)
		{	break; }

		// if the read from the client blew up, complain and exit
		if (n < 0)
		{
			printf("[-] ERROR reading from socket \n");
			closeWithoutMessage = TRUE;
			break;
		}
		
		if(buffer == NULL)
		{
			printf("[-] ERROR in input from clinet");
			break;
		}

		if (strcmp(buffer,"exit") == 0 )
			thread_exit = TRUE;


		if (-1 == system(buffer))
			returnMessage = "FAILURE";

		n = write(socket,returnMessage,BUFFER_SIZE);

		if (n < 0)
		{
			printf("[-] ERROR writing to the socket\n");
			closeWithoutMessage = TRUE;
			break;
		}
	
		//memset(returnMessage , 0 , BUFFER_SIZE);

	} 

	///made it to hear then control+c has been called.. kill the process
	returnMessage = "EXITING NOW";
	if(closeWithoutMessage == FALSE)
	{
		n = write(socket, returnMessage, strlen(returnMessage) +1);
	}

	free(returnMessage);
	close(socket);

	return 0;

}



void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	//int sockfd, newsockfd, portno, clilen;
	//struct sockaddr_in serv_addr;
	//struct sockaddr_in cli_addr;

	pthread_t session_acceptor;														  //sets up 'server'
	sl = getList();																		 //stores pthread_t ids of clients for joining
	signal(SIGINT, sigHandler);													 //set control+c call sigHandler
	int err = 0;	

	err = pthread_create(&(session_acceptor), NULL, &sessionAcceptor, NULL);

	if (err != 0)
	{
		error("\n[-]can't create session acceptor thread "); 
	}

	pthread_join(session_acceptor, NULL);
	destroyList(sl);

	return 0; 
}


