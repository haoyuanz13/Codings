package fraction;

import static org.junit.Assert.*;
import org.junit.Test;

/**
 * @author Haoyuan Zhang
 *
 */
public class FractionTest {
		
	Fraction frc1 = new Fraction(0, 5);
	Fraction frc2 = new Fraction(4, -14);
	Fraction frc3 = new Fraction(-9, 1);
		
	Fraction frc4 = new Fraction(0);
	Fraction frc5 = new Fraction(34);
	Fraction frc6 = new Fraction(-1);

	Fraction frc7 = new Fraction("  7  ");
	Fraction frc8 = new Fraction("7  / -56");
	Fraction frc9 = new Fraction("-12  ");
	Fraction frc10 = new Fraction(" -9   /   -12");		
	
	@Test
	public void testConstructor() {
		assertEquals(frc1, frc4);
		assertEquals(frc2, new Fraction(2, -7));
		
		assertEquals(frc5, new Fraction("34"));
		
		assertEquals(frc7, new Fraction(-7, -1));
		assertEquals(frc8, new Fraction(-1, 8));
	}
	
	@Test
	public void testadd() {
		Fraction temp1 = frc1.add(frc2);		
		assertEquals(temp1, frc2);
		
		Fraction temp2 = frc6.add(frc10);		
		assertEquals(temp2, new Fraction("1  / -4"));
	}
	
	@Test
	public void testsubtract() {
		Fraction temp1 = frc1.subtract(frc4);		
		assertEquals(temp1, frc4);
		
		Fraction temp2 = frc8.subtract(frc8);		
		assertEquals(temp2, frc1);
		
		Fraction temp3 = frc7.subtract(frc9);
		assertEquals(temp3, new Fraction(19));
	}
	
	@Test
	public void testmultiply() {
		Fraction temp1 = frc4.multiply(frc10);		
		assertEquals(temp1, new Fraction("   0   "));
		
		Fraction temp2 = frc9.multiply(frc10);		
		assertEquals(temp2, frc3);
	}
	
	@Test
	public void testdivide() {
		Fraction temp1 = frc2.divide(frc2);		
		assertEquals(temp1, new Fraction(-1, -1));
		
		Fraction temp2 = frc7.divide(frc8);		
		assertEquals(temp2, new Fraction(56, -1));
	}
	
	@Test
	public void testabs() {
		assertEquals(frc8.abs(), new Fraction(-1, -8));
		assertEquals(frc1.abs(), frc1);
		assertEquals(frc10, frc10.abs());
	}
	
	@Test
	public void testnegate() {
		assertEquals(frc3.negate(), new Fraction(-9, -1));
		assertEquals(frc1.negate(), frc1);
	}
	
	@Test
	public void testinverse() {
		assertEquals(frc6.inverse(), frc6);
		assertEquals(new Fraction(-4, 4).inverse(), frc6);
	}
	
	@Test
	public void testequals() {
		assertEquals(frc6.equals(frc6), true);
		assertEquals(frc4.equals(frc1), true);
	}
	
	@Test
	public void testcompareTo() {
		assertEquals(frc6.compareTo(frc6), 0);
		assertEquals(frc4.compareTo(frc1), 0);
		assertTrue(frc3.compareTo(frc9) == 1);
		assertFalse(frc9.compareTo(frc3) == 1);
		assertEquals(frc6.compareTo(frc2), -1);
	}
	
	@Test
	public void testtoString() {
		assertEquals(frc6.toString(), new Fraction(" -1  ").toString());
		assertEquals(frc1.toString(), new Fraction(0, 44).toString());
		assertEquals(frc10.toString(), new Fraction("3    / 4").toString());
		assertEquals(frc3.toString(), new Fraction(18, -2).toString());
	}
		
	
	@Test(expected=ArithmeticException.class)
	public void testDivideByZero() {		
		new Fraction(5, 0);
		new Fraction("   ");
		new Fraction("");
		new Fraction("34/0");
		frc1.inverse();
		frc4.inverse();
		frc10.divide(frc1);
		
	}
	
	@Test(expected=ClassCastException.class)
	public void testInputWrongType() {	
		frc1.compareTo(3.2);
		frc2.compareTo('a');
		frc3.compareTo(true);
		frc9.compareTo("9/7");
	}

}
