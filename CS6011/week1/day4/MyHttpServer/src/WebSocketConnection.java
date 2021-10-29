import java.io.DataInputStream;
import java.io.IOException;
import java.net.Socket;

public class WebSocketConnection {
    Socket webSocket;
    DataInputStream inputStream;
    String message;
    String JSONFormat = "";

    public WebSocketConnection(handleClient client) {
        webSocket = client.s;
        inputStream = new DataInputStream(client.input);
    }

    public void decodeData() throws IOException {
        byte[] resolverBytes = inputStream.readNBytes(2);
        int opcode = resolverBytes[0] & 0x0F;
        boolean isMasked = (resolverBytes[1] & 0x80) != 0;
        int lenGuess = resolverBytes[1] & 0x7F;
        if ( lenGuess > 125 ) {
            if ( lenGuess == 126 ) {
                byte[] guessLengthBytes = inputStream.readNBytes(2);
                lenGuess = inputStream.readUnsignedShort();
            } else if ( lenGuess == 127) {
                byte[] guessLengthBytes = inputStream.readNBytes(8);
                lenGuess = (int) inputStream.readLong();
            }
        }

        String DECODED = "";
        if (isMasked) {
            byte[] MASK = inputStream.readNBytes(4);
            byte[] ENCODED = inputStream.readNBytes(lenGuess);
            DECODED = "";

            for (int i = 0; i < ENCODED.length; i++) {
                DECODED += (char) (ENCODED[i] ^ MASK[i % 4]);
            }
            message = DECODED;
        }
        System.out.println("OPCODE: " + opcode + " | Is Masked? " + isMasked + " | Guess Length? " + lenGuess );
        System.out.println("DECODED: ");
        System.out.println( DECODED );

    }

    public void handleResponse() {
        String[] wordArray = message.split(" ");
        if (wordArray[0].equals("join")) {
            clientRoom newRelative = new clientRoom(this, wordArray[1]);
        } else {
            String user = wordArray[0];
            String userMessage = "";
            for (int i = 1; i < wordArray.length; i++) {
                userMessage += wordArray[i] + " ";
            }
            System.out.println("User: " + user + " | Message: " + userMessage);

            JSONFormat = "{ 'user': '" + user + "'; " + "'message': '" + userMessage + "'; }";
            System.out.println(JSONFormat);
        }
    }

    public void sendMessage() {
        int length = JSONFormat.length();
        int byteArrayLength = 2;
        if (length > 125) {
            if (length == 126) {
                byteArrayLength = 4;
            } else if(length == 127) {
                byteArrayLength = 10;
            }
        }
        byte[] byteArray = new byte[byteArrayLength];
        byteArray[0] = (byte) 0x81;
    }
}
