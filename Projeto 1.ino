#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};

// Vetor com 15 respostas mais recentes
int Status[15];
String readString;
int count;

// Inicia servidor da porta 80
EthernetServer server(80);

void setup() {
  
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Inicia conexão ethernet (Obtem IP):
  
  Serial.println("Initialize Ethernet with DHCP:");
  
  if (Ethernet.begin(mac) == 0) {
    
    Serial.println("Erro para obter endereço IP");

  }else {
    // Inicia o servidor
    server.begin();
    // Imprime o endereço IP do servidor
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
  }

  // Inicia todas as posições com 0  
  for(int i =0; i <15; i++){
    Status[i] = 0;
  }
}

void loop() {

  // Aguarda conexão de novos clientes
  EthernetClient client = server.available();

  // Se cliente conectou  
  if (client) {
    
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
        
    while (client.connected()) {
      if (client.available()) {
        // Le a requisição feita pelo cliente Byte por Byte
        char c = client.read();
        
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
        }
        
        if(readString.indexOf("/acende") > 0){
          Serial.println("ACENDEU");
          readString = "";
          for(int i = 15; i >= 0; i--){
            if(Status[i] == 0){
              Status[i] = 1;
              count++;
              break;
            }
            if(count == 15){
              Status[0] = 1;
            }
          }
        }else{
          if(readString.indexOf("/apaga") > 0){
            Serial.println("APAGOU");
            readString = "";
          
            for(int i = 15; i >= 0; i--){
              if(Status[i] == 0){
                Status[i] = 2;
                count++;
                break;
              }
              if(count == 15){
              Status[0] = 2;
            }
            }
          }
        }
             
        // Página WEB com os resultados
        if (c == '\n' && currentLineIsBlank) {
         
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 1");
          client.println();
          client.println("<!DOCTYPE HTML>");
          
          // Incia página web
          client.println("<html>");

            // HEAD
            client.println("<head>");

              client.println("<Title>");
                client.println("Controle do LED");
              client.println("</Title>");

              client.println("<style>");
                client.println("table, th, td { border: 1px solid black; padding: 5px; }");
              client.println("</style");
    
            client.println("</head>");
            // /HEAD

            // BODY        
            client.println("<body>");

                  if(count == 0){
                    client.println("Nenhum Sinal Recebido");
                  }else{
                    client.println("<table");
                client.println("<tr>");
                    
                    // Percorre Status, se = 1 imprime LED LIGADO
                  for(int i = 0; i < 15; i++){
                    if(Status[i] == 1){
                      client.println("<th>");
                        client.println("Status do LED: ");
                      client.println("</th>");
                      
                      client.println("<th>");
                        client.println("<font color ='00FF00'>Ligado </font>");
                      client.println("</th>");
                client.println("</tr>");
                    }

                    if(Status[i] == 2){
                      client.println("<th>");
                        client.println("Status do LED: ");
                      client.println("</th>");
                      
                      client.println("<th>");
                        client.println("<font color ='FF0000'>Desligado </font>");
                      client.println("</th>");
                client.println("</tr>");
                    }
                  }
                  client.println("</table>");
                  }
            // /BODY
            client.println("</body>");  
          //Encera pagina web
          client.println("</html>");
                        
          break;
        }
                
        if (c == '\n') {
          currentLineIsBlank = true;
        }else if (c != '\r') {
          currentLineIsBlank = false;
        } 
      }
    }

    delay(1000);
    // Encerra conexão:
    client.stop();
    // Imprime as posições de Status (Aceso = 1, Apagado = 2, Vazio = 0)
    for(int i =0; i < 15; i++){
      Serial.print("Sinal: ");
      Serial.println(Status[i]);
    }

    readString = "";
    Serial.println("client disconnected");
  }
}
