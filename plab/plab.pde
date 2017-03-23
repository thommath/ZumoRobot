/*
 * ---------- Binding the code with call javascript/serial port ----------
 */

private PLabBridge pBridge;

private String received = null;

void bindPLabBridge (PLabBridge bridge) {

  pBridge = bridge;
  
  // Vi trenger noe som hoerer etter endringer i verdi
  // We need something that listens to a change in the value
  // Vi bruker en anonym indre klasse for dette
  // We use an anonymous inner class for this
  bridge.subscribeMessages (new PLabRecv() {
    public void receive (String string) {
//      if(string.contains(" ")){
//        state = string;
//      }
      output.add(string);
      if(output.size() > 20){
        output.remove(0);
      }
//      textString1 = string;
    }
  });
  size(bridge.getWidth(), bridge.getHeight());
}

void btWrite(String string) {
  if (pBridge != null) {
    pBridge.send(string);
  }
}

//---------------------------------

ArrayList<String> output = new ArrayList<String>();

String state = "";

void setup() {
  size(300,200);              // Canvas size is 300 x 200 pixels.
  background(128);            // Background color is gray (128,128,128).
  stroke(0);                  // Stroke color is black (0,0,0)
  output.add("Hello World!");
}

void draw() {    // Called for every frame
background(0);
//    btWrite(max(min(mouseY-100, 255), 0) + "");
  for(int n = 0; n < output.size(); n++){
    text(output.get(n), 0, 50+20*n);
  }
  text(state, 100, 100);
}


void mousePressed() {
//  pressed = true;
}

void mouseReleased() {
//  pressed = false;
}