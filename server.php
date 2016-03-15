<?php
//error_reporting(0);
shell_exec('clear');
if(!($sock = socket_create(AF_INET, SOCK_STREAM, 0)))
{
	$errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);
    
    die("Couldn't create socket: [$errorcode] $errormsg \n");
}

//echo "Socket created \n";

// Bind the source address
//if( !socket_bind($sock, "192.168.1.100" , 5000) )
if( !socket_bind($sock, "localhost" , 5000) )
{
	$errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);
    
    die("Could not bind socket : [$errorcode] $errormsg \n");
}

//echo "Socket bind OK \n";

if(!socket_listen ($sock , 10))
{
	$errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);
    
    die("Could not listen on socket : [$errorcode] $errormsg \n");
}

//echo "Socket listen OK \n";
echo "\n";
echo "Waiting for incoming connections... \n";

//start loop to listen for incoming connections
while (true) 
{
	//Accept incoming connection - This is a blocking call
	$client =  socket_accept($sock);
	
	//display information about the client who is connected
	if(socket_getpeername($client , $address , $port))
	{
	//	echo "Client $address : $port is now connected to us. \n";
	}
	
	//read data from the incoming socket
	$input = socket_read($client, 1024000);
	//echo "$input";
//	echo nl2br("\n");
	//echo "***************Output**************";
		//Programing for User Interface
		if($input[0]=='*'){ 	// * is for USB
			$input[0]=' ';
		echo "\n";
			echo "USB interfaces connected are:";			
	//	echo nl2br("\n");
			$input1=split('%',$input);
			echo "";
			foreach($input1 as $var){
echo"\t".$var;
			}
			echo "\n";
		}
		else if($input[0]=='('){
			$input[0]=' ';
			echo "\n";
			echo "";
			$input1=split("%",$input);
			$z=0;
echo" ";
echo"Total RAM(MB)\tFree RAM(MB)\tShared RAM(MB)\tNo of Procs\tAvg. Load(15min)";
			echo "\n";	
			foreach($input1 as $var){
				echo $var."\t\t";
				$z++;
			//	echo nl2br("\n");			
				if($z%3==0){
					echo "";
				}
			}
			echo "";
		}
	
	// Display output  back to client
		else if($input[0]=='!'){
			$input[0]=' ';
			$input2=split(",",$input);		
//			echo nl2br("\n");
			$cpu_usage=$input2[0];
			$cpu_usage=split("%",$cpu_usage);
			$cpu_usage=$cpu_usage[0];
			echo"\nCPU usage by NODE 1 is: ".$cpu_usage;
			
			
			echo "\n";
			$f=0;
			$len=strlen($input);

			while($input[$f++]!=',');
			for($k=$f;$k<$len;$k++){
				$input[$k-$f]=$input[$k];
			}

			//echo "Refresha array is: ".$input[0].$input[1].$input[$len-$f];

			$message_sent=array();
			$m=0;
//			echo nl2br("\n");
			echo "";
			$input1=split("%",$input);
			echo "";
			$ab=0;
			$progsRunning=array();
			$cpuconusming=array();
			$m=0;
			$l=0;
			//print_r($input1);
			foreach($input1 as $var){
				$rough=$var;
//				echo nl2br("\n");	
				$rough=split(":",$rough);
//				echo nl2br("\n");
//				echo nl2br("\n");
			
				if(!strcasecmp($rough[0]," not running") || !strcasecmp($rough[0],"not running")){
					echo "\nNot running program is: ".$rough[1];
					echo "\n";
					//$resonse=(string)$rough[0];
	//				echo "Message sent is".$rough[1];
					$rough[1]=",C".$rough[1];
					
					$message_sent[$m++]=$rough[1];
					$message_sent[$m++]="%";
					
				}
				else{
					echo "\t".$var."";								
					$ab++;
					if(ctype_digit($var) && !strpos($var,".")){
						$cpuconusming[$m++]=$var;
//						echo nl2br("\n");
					//	echo " Program consumption is: ".$var;
					}
					else if(is_string($var) && !strpos($var,".")){
						$progsRunning[$l++]=$var;
			//			echo nl2br("\n");
				//		echo " Program Name is: ".$var;
					}
					else{
			//			echo nl2br("\n");
				//		echo "Memory consumption is: ".$var;
					}
					if($ab%3==0){
						echo "\n";
					}
				}
			}
			echo "";	
			echo "";
// to check whether any program is over heating
	if($cpu_usage>20){
		echo "\nWarning: CPU Usage over 20%";
//echo nl2br("\n");	
		echo "\nSearching the program with max usage";
//echo nl2br("\n");	
			$max=0;
			$maxprog="";	
			//echo $cpuconusming[$i];
			for($i=0;$i<$m;$i++){
				if($max<$cpuconusming[$i]){
					$max=$cpuconusming[$i];			
					$maxprog=$progsRunning[$i];
				//	echo $progsRunning[$i]."hello";
			
				}
			}				
//echo nl2br("\n");	
		echo "\nProgram found consuming maximum CPU usage is: ".$maxprog;
			$maxprog=",D".$maxprog;
			$message_sent[$m++]=$maxprog;
			$message_sent[$m++]="%";
	}	
			
//		
			$messg=implode("",$message_sent);
		//	echo "See the message".$messg;
			socket_write($client, $messg);
		}
		
//	socket_write($client, $response);
	socket_close($client);

}
?>