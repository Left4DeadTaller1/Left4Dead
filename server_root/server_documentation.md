# Server Documentation

## Installation and Execution Instructions
1. Clone the repository: `git clone git@github.com:Left4DeadTaller1/Left4Dead.git`
2. Install the required dependencies: 
   | Library         | Installation Command                   |
   |-----------------|----------------------------------------|
   | `yaml.cpp`      | `sudo apt-get install libyaml-cpp-dev` |
   | `googletest`    | `sudo apt-get install libgtest-dev`    | -> go to item 2.1


   2.1  to correctly install googletest, follow this instructions:
      - after running sudo apt-get install libgtest-dev, go to /usr/src/googletest
      with cd /usr/src/googletest
      -Create a build directory within the Google Test source directory.
      with sudo mkdir build
      -Switch to that directory.
      with cd build
      -Run cmake with sudo cmake ..
      -Run make with sudo make
      Install the Google Test library:
      sudo make install
   
3. Build the project: Follow the build instructions provided in the repository's documentation.
   - go to build folder
   - i will recommend deleting the previous contents of the build folder with "rm -r *"
   - run cmake ..
   - run make (first time takes a while)
4. Run the server: `./server <port>` like `./server 8080`

## Server Structure
   Server: Which is the one that is in charge of launching acceptor and listening to the input in case they enter the letter "q".

   Acceptor: Responsible for accepting incoming client connections, when it accepts a client it creates a ClientConnection object to handle the communication between the server and the clients, adding it to a list of clients. Is also in charge of removing inactive players.

   GamesManager: The Monitor of the Games, is responsible for creating and deleting matches, and for adding and removing players from matches. Its the class the clients interact with to create and join matches. It also is the one in charge of removing inactive matches.

   ClientConnection: This class handles the communication between the server and a specific client, it is the representation of the client on the server. It has ownership of the socket that Acceptor passed to it, and two communication threads ClientSender and ClientReceiver, and a reference to the MatchManager object that is the match monitor class.

   ClientReceiver: This class inherits from the Thread class and is responsible for receiving and processing messages from the client. It contains a reference to the Socket, a Queue to communicate with the Sender, a Protocol object to receive and process messages from the client, and a reference to the MatchManager object to join matches. When it receives an action from the client, it creates an Action object corresponding to the action received and pushes it to the Action Queue of the game.

   ClientSender: This class also inherits from the Thread class and is responsible for sending messages to the client. Contains the Socket and the Action Queue. The ClientSender class is responsible for sending the messages to the client.
   The Sender will pop the game state from its queue and will send it to the client. The Sender will also send any other  message the game wants to communitcate to the client, such as the game over message.

   Protocol: This class contains methods to encode and decode actions and messages between the server and the client. It is used by the ClientReceiver and ClientSender classes to process the messages, and by the game to encode the gameState. 

## Game Structure

   The game loop is divided in 3 main sections:
   - getPlayersActions: This section retrieves player actions from the action queue. Players push their inputs to the game  big action queue, and this process involves popping actions from the queue and adding them to the corresponding player's action queue. The action is assigned to the player based on their ID. This allows the game to instead of having to inmediately process the action the moment you pop it from the queue, to do so in the updateState part of the game loop.

   - updateState: This is the core part of the game loop where the game logic takes place. It iterates over all entities in the game, (players and zombies). For each entity, if it is a player the player's action state is set according to the input they provided, such as walking, shooting, or reloading, (basically sets the player's actionState attribute). Additionally, the action counter attribute is set to the appropriate duration (kinda like a State pattern). The loop then invokes each action method, which checks if the action state matches the corresponding method and performs the action accordingly. For example, the "reloadPlayer" method checks if the player's action state is set to "Reloading" and triggers the reloading process.

   For zombies, a similar logic applies, but instead of user inputs, they decide their target using the "decideTarget" method. Zombies set their target as the closest alive player (if the action counter is 0), and then they perform the corresponding action accordingly.

   After iterating over the entities, the game removes away-from-keyboard (AFK) or disconnected players. This step is placed after the loop to avoid modifying the entity list while iterating, which can lead to errors (got tons of segmentation faults for removing them while iterating over the list). Additionally, every minute, the zombies mutate making them stronger and faster, and a new zombie is spawned every X seconds (depending on the configuration).

   - sendState: This final section of the game loop is responsible for sending the game state to the players. It retrieves the DTO for each entity and sends them to the server protocol. The server protocol then translates the DTOs into bytes. Finally, the encoded game state is pushed to each player's queue, from which the Sender component sends it to the corresponding client.


 
 