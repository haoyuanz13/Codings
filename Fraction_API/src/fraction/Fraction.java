package fraction;
/**
 * Fraction Class
 * @author Haoyuan Zhang
 */
public class Fraction implements Comparable<Object>{
  private int nume;
  private int deno;
  
  /**
   * Constructor that takes <i>two integers</i> as parameters.
   * @param numerator Represents numerator in fraction.
   * @param denominator Represents denominator in fraction.
   */
  public Fraction(int numerator, int denominator){
    this.nume = numerator;
    this.deno = denominator;
    
    if (this.deno == 0){
      throw new ArithmeticException("Divide by zero!"); 
    }
    
    int[] nor = normalize(this.nume, this.deno);
    this.nume = nor[0];
    this.deno = nor[1];
  }
  
  /**
   * Constructor that takes <i>one integer</i> as parameter.
   * @param wholeNumber Represents numerator in fraction.
   */
  public Fraction(int wholeNumber){
    this.nume = wholeNumber;
    this.deno = 1;
  }
  
  /**
   * Constructor that takes <i>string</i> as parameter. 
   * @param fraction Represents the whole fraction.
   * @exception ArithmeticException on denominator equals to zero.
   */
  public Fraction(String fraction){
    fraction = fraction.trim();   // handle the case that blanks around integers
    
    if (fraction.isEmpty()){
      throw new ArithmeticException("Not a fraction!");
    }
      
    else if (fraction.indexOf('/') == -1){      // handle the case that input is integer
      this.nume = Integer.parseInt(fraction);
      this.deno = 1;
    }
    else{
      String[] num = fraction.split("/");
      String nu = num[0].trim();
      String de = num[1].trim();
      this.nume = Integer.parseInt(nu);
      this.deno = Integer.parseInt(de);
      
      if (this.deno == 0) throw new ArithmeticException("Divide by zero!");   // handle the case that denominator is zero 
      
      int[] nor = normalize(this.nume, this.deno);    // normalize
      this.nume = nor[0];
      this.deno = nor[1];     
    }   
  }
  
  /**
   * <b>Add</b> two fractions and return sum.
   * @param f Input adding fraction.
   * @return Sum of this and input adding fraction f.
   */
  public Fraction add (Fraction f){
    Fraction res = new Fraction(1);
    res.nume = this.nume * f.deno + this.deno * f.nume;
    res.deno = this.deno * f.deno;
    
    int[] nor = normalize(res.nume, res.deno);
    res.nume = nor[0];
    res.deno = nor[1];
    return res;   
  }
  
  /**
   * <b>Subtract</b> two fractions and return its difference.
   * @param f Fraction which is subtracted.
   * @return Difference between this and input fraction f.
   */
  public Fraction subtract (Fraction f){
    Fraction res = new Fraction(1);
    res.nume = this.nume * f.deno - this.deno * f.nume;
    res.deno = this.deno * f.deno;
    
    int[] nor = normalize(res.nume, res.deno);
    res.nume = nor[0];
    res.deno = nor[1];
    return res;   
  }
  
  /**
   * <b>Multiply</b> two fractions and return its product. 
   * @param f One of the multiply fractions.
   * @return Product of this and input fraction f.
   */
  public Fraction multiply (Fraction f){
    Fraction res = new Fraction(1);
    res.nume = this.nume * f.nume;
    res.deno = this.deno * f.deno;
    
    int[] nor = normalize(res.nume, res.deno);
    res.nume = nor[0];
    res.deno = nor[1];
    return res;   
  }
  
  /**
   * Implement <b>division</b> and return quotient.
   * @param f Divisor.
   * @return Quotient of dividing this by divisor f.
   * @exception ArithmeticException on divisor equals to zero.
   */
  public Fraction divide (Fraction f){
    Fraction res = new Fraction(1);
    res.nume = this.nume * f.deno;
    res.deno = this.deno * f.nume;
    if (res.deno == 0) throw new ArithmeticException("Divide is illegal!");
    
    int[] nor = normalize(res.nume, res.deno);
    res.nume = nor[0];
    res.deno = nor[1];
    return res;   
  }
  
  /**
   * Get the <b>absolute value</b> of this fraction.
   * @return Absolute value of this fraction.
   */
  public Fraction abs(){
    Fraction res = new Fraction(1);
    res.nume = Math.abs(this.nume);
    res.deno = this.deno;
    return res; 
  }
  
  /**
   * Get <b>opposite value</b> of this fraction.
   * @return Same numeric value of this fraction with <i>opposite sign</i>.
   */
  public Fraction negate(){
    Fraction res = new Fraction(1);
    res.nume = -1 * this.nume;
    res.deno = this.deno;
    return res; 
  }
  
  /**
   * Get <b>reciprocal</b> of this fraction.
   * @return Reciprocal of this fraction.
   * @exception ArithmeticException on numerator equals to zero.
   */
  public Fraction inverse(){
    Fraction res = new Fraction(1);
    if (this.nume == 0){
      throw new ArithmeticException("The fraction doesn't have inverse form!");
    }
    
    int flag = 1;
    if (this.nume < 0) flag = -1;
    
    res.nume = flag * Math.abs(this.deno);
    res.deno = Math.abs(this.nume);
    return res; 
  }
  
  /**
   * Test whether two fractions are <b>equal</b>.
   * @param o Fraction to compare.
   * @return <b>True</b> if o is a fraction and equals to this;<p>
   * <b>False</b> in all other cases. 
   * @exception ClassCastException on wrong input type.
   */
  @Override
  public boolean equals(Object o) throws ClassCastException{
    if (o instanceof Fraction){
      Fraction result = this.subtract ((Fraction) o);
      return result.nume == 0;
    }else return false;   
  }
  
  /**
   * <b>Compare</b> two fractions.
   * @param o Fraction or integer to compare.
   * @return <b>Negative integer</b> if this is less than o;<p>
   * <b>Zero</b> if this is equal to o;<p>
   * <b>Positive integer</b> if this is greater than o.
   * @exception ClassCastException on wrong input type.
   */
  @Override
  public int compareTo(Object o) throws ClassCastException{
    Fraction input = new Fraction(0);
    
    if (o instanceof Fraction){
      input = (Fraction) o;     
    }else if (o instanceof Integer){
      input = new Fraction((int) o);
    }else {
      throw new ClassCastException("Compare parameter is neither a fraction nor integer!");
    }
    
    Fraction result = this.subtract(input);
    if (result.nume == 0) return 0;
    else if (result.nume > 0) return 1;
    else return -1;     
  }
  
  /**
   * <b>Print out</b> fraction.
   * @return String of the form n/d;<p>
   * n is the numerator and d is the denominator.
   */
  @Override
  public String toString(){   
    String res = new String();
    
    if (this.deno == 1) 
      res = String.valueOf(this.nume);
    else 
      res = String.valueOf(this.nume) + "/" + String.valueOf(this.deno);    
    return res;
  }
  
  /**
   * Normalize fraction.
   * @param numa Numerator in fraction.
   * @param numb Denominator in fraction.
   * @return Array with integer whose size is two,
   * first element is normalized numerator;
   * second element is normalized denominator. 
   */
  private int[] normalize(int numa, int numb) {
    int[] res = new int [2];
    int flag = 1;
    if (numa * numb < 0) flag = -1;
    
    if (numa * numb == 0){
      res[0] = 0;
      res[1] = 1;
    }else{
      int div = gcd(Math.abs(numa), Math.abs(numb));  // compute greatest common divisor 
      res[0] = flag * Math.abs(numa) / div;
      res[1] = Math.abs(numb) / div;    
    }
    return res;
  }
  
  /**
   * Compute GCD(Greatest Common Divisor).
   * @param numa Numerator in fraction. 
   * @param numb Denominator in fraction.
   * @return GCD of numerator and denominator. 
   */
  private int gcd(int numa, int numb) {
    if(numa == 0) return numb;
    if(numb == 0) return numa;
    
    while (numb != 0){
      int remainder = numa % numb;
      numa = numb;
      numb = remainder;
    }
    return numa;
  }
}
