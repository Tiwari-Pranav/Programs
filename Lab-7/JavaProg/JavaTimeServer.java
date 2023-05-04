import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class JavaTimeServer {
    
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java TimeServer <port number>");
            System.exit(1);
        }

        int port = Integer.parseInt(args[0]);

        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Time Server listening on port " + port + "...");
            
            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("Client connected: " + clientSocket.getInetAddress().getHostAddress());
                
                OutputStream out = clientSocket.getOutputStream();
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
                String timeString = LocalDateTime.now().format(formatter);
                out.write(timeString.getBytes());
                out.flush();
                
                clientSocket.close();
            }
        } catch (IOException e) {
            System.err.println("Exception caught");
            System.err.println(e.getMessage());
        }
    }
}

