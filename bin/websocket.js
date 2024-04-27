const WebSocket = require('ws');
const EventEmitter = require('events');


class WebSocketService extends EventEmitter {
    constructor() {
        super();
        this.wsConnection = null;

    }
    
    createWebSocketServer(server) {
        const wss = new WebSocket.Server({ server });

        wss.on('connection', (ws) => {
            console.log('New WebSocket connection!');
            this.handleWebSocketConnection(ws);
        });

        return wss;
    }

    handleWebSocketConnection(ws) {
        this.wsConnection = ws;
        this.emit('connected'); // Emit an event when the connection is established

        // Handle incoming messages
        ws.on('message', (message) => {
            this.handleIncomingMessage(ws, message);
        });

        // Handle connection closure
        ws.on('close', () => {
            this.handleConnectionClose(ws);
        });
    }

    sendRequests(queries) {
        if (this.wsConnection) {
            // queries.forEach((query) => { //an array of queries sending out official 
            this.wsConnection.send(JSON.stringify({ action: 'retrieve_data', params: { key: queries } }));
            // });
        } else {
            console.error('No active WebSocket connection');
        }
    }

    handleIncomingMessage(ws, message) {
        try {
            const parsedMessage = JSON.parse(message);

            if (parsedMessage.data) {
                let Data = JSON.parse(parsedMessage.data);
                
                console.log('Saving received data into strucrure!!');
                // console.log('Data type:', typeof userData);
                this.emit('dataReceived', Data);
            } else {
                console.error('Received message without data property:', parsedMessage);
            }
        } catch (error) {
            console.error('Error parsing message:', error);
        }
    }

    handleConnectionClose(ws) {
        console.log('WebSocket connection closed');
        this.wsConnection = null;
    }
}

const websocketService = new WebSocketService();
module.exports = websocketService;
