import java.io.*;
import java.net.*;

public class JavaTimeClient {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java TimeClient <hostname> <port>");
            System.exit(1);
        }

        String hostname = args[0];
        int port = Integer.parseInt(args[1]);

        try (
            Socket socket = new Socket(hostname, port);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        ) {
            String time = in.readLine();
            System.out.println("Current time: " + time);
        } catch (IOException e) {
            System.err.println("Error communicating with server: " + e.getMessage());
            System.exit(2);
        }
    }
}

