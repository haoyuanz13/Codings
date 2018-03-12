package fraction;
import java.util.Scanner;

/**
 * Calculator implements operations based on commands by users.
 * @author Haoyuan Zhang
 */
public class FractionCalculator {
  Scanner scanner = new Scanner(System.in); 
  public static void main(String args[]) {
    new FractionCalculator().run();     
  }

  
  /**
   * Plays a role as main program.<p> 
   * Based on input instruction, do corresponding calculation.<p>
   * Print out current result.
   * @exception ArithmeticException on illegal commands or operations.
   */
  public void run() {
    Fraction cur = new Fraction(0);
    System.out.println(cur);

    while (true){
      System.out.println("\nPlease input your command: ");
      String operate = scanner.nextLine();
      operate = operate.trim();

      if (operate.isEmpty() || !valid(operate)){                             // test the input form
        System.out.println("Your command is illegal. please input again.");  // if input form is illegal, show warning and ask for new input
        continue;
      }

      if (operate.equals("q")){                                              // the instruction of quitting calculator
        quit();
        break;
      } 

      try{
        char command = operate.charAt(0);                                  // based on command do different operations 
        switch(command) {
          case 'a': cur = abs(cur);
          break;
        
          case 'c': cur = clear();
          break;
        
          case 'i': cur = invert(cur);
          break;
        
          case 's': cur = replace(operate.substring(2));
          break;
        
          case '+': cur = add(cur, operate.substring(2));
          break;
        
          case '-': cur = sub(cur, operate.substring(2));
          break;
        
          case '*': cur = multi(cur, operate.substring(2));
          break;
        
          case '/': cur = div(cur, operate.substring(2));
          break;        
        }  
      }
      
      catch(ArithmeticException e){
        System.out.println("Illegal operations! Please check again.");
      }

      finally{
        System.out.println("current result is: "+ cur);     
      }         
    }    
  }
  
  /**
   * Test whether input instruction is <b>legal</b> or not.
   * @param ope Represents user's instruction.
   * @return True if command is legal.<p> 
   * False if command is illegal.
   */
  public boolean valid(String ope) { 
    if(ope.length() < 1) return false;

    String opset = "aciqs+-*/";
    int flag = opset.indexOf(ope.charAt(0));
    if (flag == -1) return false;              // instructions that cannot be found in commands set
    else if(flag >=0 && flag < 4){             // instructions that need only one command character
      if (ope.length() > 1) return false;
      else return true;
    }
    else{                                      // instructions that need one more characters after command character
      if (ope.length() <= 2) return false;
    }

    if(!(ope.charAt(1) == ' ')) return false;  // no required white space after initial command character 
    String sub = ope.substring(2);
    sub = sub.trim();
    sub += '*';                                // stop label to avoid index out of range
    int ind = 0;
    int count = 0;

    if(sub.charAt(ind) == '-' || sub.charAt(ind) == '+') ind ++;   
    while(sub.charAt(ind) >= '0' && sub.charAt(ind) <= '9'){
      ind ++;
      count ++;
    }

    if (count == 0) return false;                // no detect integer
    if (ind == sub.length() - 1) return true;    // input is integer form without slash  

    while (sub.charAt(ind) == ' ') ind ++;    
    if (sub.charAt(ind) == '/') ind ++;

    count = 0;
    while (sub.charAt(ind) == ' ') ind ++;

    if(sub.charAt(ind) == '-' || sub.charAt(ind) == '+') ind ++;
    while(sub.charAt(ind) >= '0' && sub.charAt(ind) <= '9'){
      ind ++;
      count ++;
    }
    if (count == 0) return false;
    return ind == sub.length() - 1;            // only index equals to last position of string means legal instruction
  }


  /**
   * <b>Absolute value </b> of display fraction.
   * @param cur Current display number.
   * @return Absolute value of cur.
   */
  public Fraction abs(Fraction cur) {
    return cur.abs();
  }
  
  /**
   * <b>Clear</b> the calculator.
   * @return 0 which is the reset number of calculator. 
   */
  public Fraction clear() {
    Fraction res = new Fraction(0);
    return res;
  }
  
  /**
   * <b>Invert</b> the currently display number.
   * @param cur Current display number;
   * @return Inverse number of cur.
   * @exception ArithmeticException on cur equals to zero. 
   */
  public Fraction invert(Fraction cur) {
    return cur.inverse();   
  }

  /**
   * <b>Discard</b> current display number and <b>replace</b> it with new input fraction.
   * @param ope Represents the number to replace current display one.
   * @return New display number.
   */
  public Fraction replace(String ope) {
    Fraction n = normali(ope);
    return n;
  }
  
  /**
   * <b>Quit</b> the program.
   */
  public void quit() {
    System.out.println("Calculator quit.");
  }

  /**
   * <b>Add</b> certain fraction to the number currently display.
   * @param cur Current display fraction.
   * @param ope Adding fraction.
   * @return Sum of cur and ope.
   */
  public Fraction add(Fraction cur, String ope) {
    Fraction n = normali(ope);
    return cur.add(n);
  }
  
  /**
   * <b>Subtract</b> certain fraction from the number currently display.
   * @param cur Current display fraction represents subtractor.
   * @param ope Represents subtrahend.
   * @return Difference between cur and ope.
   */
  public Fraction sub(Fraction cur, String ope) {
    Fraction n = normali(ope);
    return cur.subtract(n);
  }

  /**
   * <b>Multiply</b> the number currently display by certain fraction. 
   * @param cur Current display fraction represents one of the multiply parameters.
   * @param ope Certain fraction represents one of the multiply parameters.
   * @return Product of cur and ope.
   */
  public Fraction multi(Fraction cur, String ope) {
    Fraction n = normali(ope);
    return cur.multiply(n);   
  }
  
  /**
   * <b>Divide</b> the number currently display by certain fraction.
   * @param cur Current display fraction represents dividend. 
   * @param ope Certain fraction represents divisor.
   * @return Quotient of dividing cur by ope.
   */
  public Fraction div(Fraction cur, String ope) {
    Fraction n = normali(ope);
    return cur.divide(n);
  }
  
  /**
   * <b>Normalized</b> fraction. 
   * @param ope Legal input fraction.
   * @return Normalized fraction.
   */
  public Fraction normali(String ope){
    ope = ope.trim();
    String res = new String();
    for (int ind = 0; ind < ope.length(); ind ++){
      if (ope.charAt(ind) == ' ' || ope.charAt(ind) == '+') continue;
        res = res + ope.charAt(ind);
    }
    Fraction n = new Fraction(res);
    return n;   
  }   

}
