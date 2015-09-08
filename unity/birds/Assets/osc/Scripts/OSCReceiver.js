
public var RemoteIP : String = "127.0.0.1"; //127.0.0.1 signifies a local host (if testing locally
public var SendToPort : int = 9000; //the port you will be sending from
public var ListenerPort : int = 8050; //the port you will be listening on
public var controller : Transform;
public var gameReceiver = "Cube"; //the tag of the object on stage that you want to manipulate
private var handler : Osc;

//VARIABLES YOU WANT TO BE ANIMATED
private var scaleVal : float = 1;
private var xVal: float = 0;
private var yVal: float = 0;
private var zVal: float = 0;

private var scaleValX: int = 1;
private var scaleValY: int = 1;
private var scaleValZ: int = 1;

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
	go.transform.localScale = new Vector3(scaleVal, scaleVal, scaleVal);	
	go.transform.localPosition = new Vector3(xVal,yVal,zVal);

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
			//go.transform.Translate(xVal,0,0,Space.World);
			break;
		case "/MurmurBirds/position/y":
			yVal = msgValue;
			//go.transform.Translate(0,yVal,0,Space.World);
			break;
		case "/MurmurBirds/position/z":
			zVal = msgValue;
			//go.transform.Translate(0,0,zVal,Space.World);
			break;
		case "/MurmurBirds/swarmScale":
			scaleVal = msgValue;
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

