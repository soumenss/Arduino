void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly
  int a = 1;
  Serial.println(fact(a));
  delay(100);
  a++;
}

int fact(int n){
  if(n>1){
    return n* fact(n-1);
  }
  else{
    return 1;
  }
}
