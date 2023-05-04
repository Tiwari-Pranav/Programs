// A Java program for a Client
import java.io.*;
import java.net.*;
import java.sql.Timestamp;
import java.util.Date;

public class Client {
    // initialize socket and input output streams
    private Socket socket = null;
    private BufferedReader input = null;
    private DataOutputStream out = null;
	private DataInputStream in=  null;
 
    // constructor to put ip address and port
    public Client(String address, int port) throws IOException
    {
        // establish a connection
        try {
            socket = new Socket(address, port);
            System.out.println("Connected");
 
            // takes input from terminal
            input = new BufferedReader (new InputStreamReader(System.in));
 
            // sends output to the socket
            out = new DataOutputStream(
                socket.getOutputStream());

			in = new DataInputStream(
					new BufferedInputStream(socket.getInputStream()));
				
        }
        catch (UnknownHostException u) {
            System.out.println(u);
            return;
        }
        catch (IOException i) {
            System.out.println(i);
            return;
        }
 
        // string to read message from input
        String line = "";
 
        // keep reading until "Over" is input
        while (!line.equals("Over")) {
            try {
				Date date = new Date();
                System.out.println("\n"+new Timestamp(date.getTime())+" Message : ");
                line = input.readLine();
                out.writeUTF(line);
				line = in.readUTF();
				if(!line.equalsIgnoreCase("Over"))
				{
				System.out.println(new Timestamp(date.getTime())+" Response : ");
                System.out.println(line);
				}
				else
				System.out.println("Connection terminated");
            }
            catch (IOException i) {
                System.out.println(i);
            }
        }
 
        // close the connection
        try {
            input.close();
            out.close();
            socket.close();
        }
        catch (IOException i) {
            System.out.println(i);
        }
    }
 
    public static void main(String args[]) throws IOException
    {
        Client client = new Client("127.0.0.1", 5000);
    }
}