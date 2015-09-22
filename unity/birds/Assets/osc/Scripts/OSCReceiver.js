
public var RemoteIP : String = "127.0.0.1"; //127.0.0.1 signifies a local host (if testing locally
public var SendToPort : int = 9000; //the port you will be sending from
public var ListenerPort : int = 8050; //the port you will be listening on
public var controller : Transform;
public var gameReceiver = "Murmur Birds"; //the tag of the object on stage that you want to manipulate
public var gameReceiverScript = "FlockController"; 

private var handler : Osc;

//VARIABLES YOU WANT TO BE ANIMATED
private var scaleVal : float = 1;
private var xVal: float = 0;
private var yVal: float = 0;
private var zVal: float = 0;

private var flockSize: float = 15;
private var birdSize: float = 1.0;

private var speed: float = 15;
private var childAmount: int = 150;

//private var go: GameObject;
//var go = GameObject.Find(gameReceiver);

public function Start ()
{
	//Initializes on start up to listen for messages
	//make sure this game object has both UDPPackIO and OSC script attached

	var udp : UDPPacketIO = GetComponent("UDPPacketIO");
	udp.init(RemoteIP, SendToPort, ListenerPort);
	handler = GetComponent("Osc");
	handler.init(udp);
	handler.SetAllMessageHandler(AllMessageHandler);
	
}
Debug.Log("Running");

function Update () {
	var go = GameObject.Find(gameReceiver);
	
	go.transform.localPosition = new Vector3(xVal,yVal,zVal);
	
	go.GetComponent(gameReceiverScript)._maxSpeed = speed;
	go.GetComponent(gameReceiverScript)._minSpeed = speed*0.6;
	
	go.GetComponent(gameReceiverScript)._maxAnimationSpeed = speed/5.0;
	go.GetComponent(gameReceiverScript)._minAnimationSpeed = speed/10.0;
	
	
	go.GetComponent(gameReceiverScript)._maxScale = birdSize;
	go.GetComponent(gameReceiverScript)._minScale = birdSize*0.7;
	go.GetComponent(gameReceiverScript)._childAmount = childAmount;
		
	go.GetComponent(gameReceiverScript)._spawnSphere = flockSize;
	go.GetComponent(gameReceiverScript)._spawnSphereHeight = flockSize;
	go.GetComponent(gameReceiverScript)._spawnSphereDepth = flockSize;
}

//These functions are called when messages are received
//Access values via: oscMessage.Values[0], oscMessage.Values[1], etc

public function AllMessageHandler(oscMessage: OscMessage){

	var msgString = Osc.OscMessageToString(oscMessage); //the message and value combined
	var msgAddress = oscMessage.Address; //the message parameters
	var msgValue = oscMessage.Values[0]; //the message value
	Debug.Log(msgString); //log the message and values coming from OSC

	//FUNCTIONS YOU WANT CALLED WHEN A SPECIFIC MESSAGE IS RECEIVED
	switch (msgAddress){
		case "/MurmurBirds/position/x":
			xVal = msgValue;
			break;
		case "/MurmurBirds/position/y":
			yVal = msgValue;
			break;
		case "/MurmurBirds/position/z":
			zVal = msgValue;
			break;
		case "/MurmurBirds/birdSize":
			birdSize = msgValue;
			break;
			
		case "/MurmurBirds/swarmSize":
			flockSize = msgValue;
			break;
			
		case "/MurmurBirds/speed":
			speed = msgValue;
			break;
		case "/MurmurBirds/swarmNumber":
			childAmount = msgValue;
			break;
		default:
			//
			break;
	}

}


//FUNCTIONS CALLED BY MATCHING A SPECIFIC MESSAGE IN THE ALLMESSAGEHANDLER FUNCTION
public function Rotate(msgValue) : void //rotate the cube around its axis
{
	yRot = msgValue;
}

