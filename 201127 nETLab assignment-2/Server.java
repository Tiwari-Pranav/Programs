
// A Java program for a Server
import java.net.*;
import java.io.*;
import java.io.File;
import java.util.Scanner;
import java.sql.Timestamp;
import java.util.Date;

public class Server {
    // initialize socket and input stream
    private Socket socket = null;
    private ServerSocket server = null;
    private DataInputStream in = null;
    private BufferedReader input = null;
    private DataOutputStream out = null;

    // constructor with port
    public Server(int port) throws IOException {

        // starts server and waits for a connection
        try {
            server = new ServerSocket(port);
            System.out.println("Server started");

            System.out.println("Waiting for a client ...");

            socket = server.accept();
            System.out.println("Client accepted");

            input = new BufferedReader(new InputStreamReader(System.in));
            // takes input from the client socket
            in = new DataInputStream(
                    new BufferedInputStream(socket.getInputStream()));

            out = new DataOutputStream(
                    socket.getOutputStream());
            String line = "";

            // reads message from client until "Over" is sent
            while (!line.equals("Over")) {
                try {
                    Date date = new Date();
                    line = in.readUTF();
                    if (line.charAt(0) == '/') {
                        String cmd = line.substring(1, line.indexOf(' '));
                        String path = line.substring(line.indexOf(' ') + 1);
                        if (cmd.equalsIgnoreCase("list")) {
                            System.out.println("\n"+new Timestamp(date.getTime())+ " Command request: \n"+line);
                            File directoryPath = new File("/home/emperor-kautilya" + path);
                            String output = "";
                            String contents[] = directoryPath.list();
                            for (int i = 0; i < contents.length; i++) {
                                output = output + contents[i] + "\n";
                            }
                            System.out.println(new Timestamp(date.getTime())+" : \nResponse Sent!!");
                            out.writeUTF(output);
                        } else if (cmd.equalsIgnoreCase("show")) {
                            System.out.println("\n"+new Timestamp(date.getTime())+ " Command request: \n"+line);
                            File filePath = new File("/home/emperor-kautilya" + path);
                            Scanner fileread = new Scanner(filePath);
                            String output = "";

                            while (fileread.hasNextLine()) {
                                output = output + fileread.nextLine() + "\n";
                            }
                            System.out.println(new Timestamp(date.getTime())+" : \nResponse Sent!!");
                            fileread.close();
                            out.writeUTF(output);
                        }
                    }else if(!line.equalsIgnoreCase("Over"))
                    {
                        System.out.println("\n"+new Timestamp(date.getTime())+" Client : ");
                        System.out.println(line);
                        System.out.println(new Timestamp(date.getTime())+" Response : ");
                        line = input.readLine();
                        out.writeUTF(line);
                    }
                    else{
                        out.writeUTF("Over");
                    }

                } catch (IOException i) {
                    System.out.println(i);
                }
            }
            System.out.println("Closing connection");

            // close connection
            socket.close();
            in.close();
        } catch (

        IOException i) {
            System.out.println(i);
        }
    }

    public static void main(String args[]) throws IOException {
        Server server = new Server(5000);
    }
}