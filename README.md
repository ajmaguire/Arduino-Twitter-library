# Twitter client library for Arduino
A library to post tweets to Twitter from Arduino via Ethernet and WiFi.
This library uses relay server on GooleAppEngine to handle OAuth authentication:

http://arduino-tweet.appspot.com/

## Example
Below is a simple example of how to use the WiFi portion of the library:

//BEGIN EXAMPLE

 char tweet[512]; // the character buffer for your tweet.
 
 sprintf(tweet, "Hello world!"); // put characters in the buffer.
 
 
 TwitterWiFi twitter("YOUR CODE"); // instantiate a TwitterWiFi object.
 
 twitter.post(tweet);  // post the tweet you wrote above!
 
 
//END EXAMPLE


## How to use
 + Add this library to your Arduino IDE.
 
 + Get a token to post a message using OAuth from the relay server:
   
   http://arduino-tweet.appspot.com/ -> "Step 1."
    
   When you allow the access, your token is issued.

 + Pass your token to the constructor of Twitter class, like:

        Twitter twitter("YOUR-TOKEN");

## Reference
### Creation
You need to create an instance of a Twitter or TwitterWiFi class like below:

    TwitterWiFi twitter("YOUR-TOKEN"); // for WiFi.
          or...
    Twitter twitter("YOUR-TOKEN"); // for ethernet.

You need also begin said library.

### Functions
#### bool post(const char *message)

Begin posting the specified message to Twitter. If connection to twitter.com is established successfully, this function returns true.

If failed to connect Twitter, returns false. (Check Ethernet/WiFi is correctly configured.)

Posting is not done yet even it returns true. You should call twitter.checkStatus() periodically or twitter.wait().

#### bool checkStatus(Print *debug = NULL)

Check if the posting request is running. Returns true if it's still running.

You can specify the debug argument to output the response from server for debugging, e.g.

    checkStatus(&Serial);

#### int status(void)

Returns the HTTP status code in response from Twitter, e.g. 200 - OK.

Only available after posting the message is done and checkStatus() returns false.

#### int wait(Print *debug = NULL)

Wait until posting the message is done. Return value of this function is HTTP status code in response from Twitter.

Equivalent to the code below:

    while (checkStatus(debug));
        return statusCode;

