
// A Java program for a Server
import java.net.*;
import java.io.*;

public class Server {

    public static void main(String args[]) {
        int port = 8080; // web server port

        // starts server and waits for a connection
        try {
            ServerSocket server = new ServerSocket(port);
            System.out.println("Server started");

            System.out.println("Status: Waiting for a client ...");

            Socket socket = server.accept();
            System.out.println("Status: Client accepted");

            // takes input from the client socket
            DataInputStream in = new DataInputStream(
                    new BufferedInputStream(socket.getInputStream()));

            String line = "";
            System.out.println("\nMessages: ");
            // reads message from client until "Over" is sent
            while (!line.equals("Over")) {
                try {
                    line = in.readUTF();
                    System.out.println(line);

                } catch (IOException i) {
                    System.out.println(i);
                }
            }
            System.out.println("Closing connection");

            // close connection
            socket.close();
            in.close();
            server.close();
        } catch (IOException i) {
            System.out.println(i);
        }
    }
}
