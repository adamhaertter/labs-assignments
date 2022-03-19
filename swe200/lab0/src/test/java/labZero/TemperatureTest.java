package labZero;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

import org.junit.Test;

public class TemperatureTest {
  
  @Test
  public void testUninitialized() {
    try {
      Temperature t = new Temperature();
      t.getCelsius();
      fail();
    } catch (TemperatureException e) {
      //This is expected
    }
  }
  
  @Test
  public void testInvalidTemperatureKelvin() {
    try {
      Temperature t = new Temperature();
      t.setByKelvin(-1);
      fail();
    } catch (TemperatureException e) {
      //Expected
    }
  }
  
  @Test
  public void testCtoC() {
    try {
      Temperature t = new Temperature();
      t.setByCelsius(20);
      t.getCelsius();
    } catch (TemperatureException e) {
      //Not expected
    }
  }
  
  @Test
  public void testFtoF() {
    try {
      Temperature t = new Temperature();
      t.setByFahrenheit(20);
      t.getFahrenheit();
    } catch (TemperatureException e) {
      //Not expected
    }
  }
  
  @Test
  public void testKtoK() {
    try {
      Temperature t = new Temperature();
      t.setByKelvin(20);
      t.getKelvin();
    } catch (TemperatureException e) {
      //Not expected
    }
  }
  
  private static final double DELTA = 0.01;
  
  @Test
  public void testCtoF() {
    Temperature t = new Temperature();
    t.setByCelsius(0);
    assertEquals(32, t.getFahrenheit(), DELTA);
  }
  
  @Test
  public void testCtoK() {
    Temperature t = new Temperature();
    t.setByCelsius(-273.15);
    assertEquals(0.0, t.getKelvin(), DELTA);
  }
  
  @Test
  public void testFtoC() {
    Temperature t = new Temperature();
    t.setByFahrenheit(32);
    assertEquals(0.0, t.getCelsius(), DELTA);
  }
  
  @Test
  public void testFtoK() {
    Temperature t = new Temperature();
    t.setByFahrenheit(-459.67);
    assertEquals(0.0, t.getKelvin(), DELTA);
  }
  
  @Test
  public void testKtoC() {
    Temperature t = new Temperature();
    t.setByKelvin(0);
    assertEquals(-273.15, t.getCelsius(), DELTA);
  }
  
  @Test
  public void testKtoF() {
    Temperature t = new Temperature();
    t.setByKelvin(0.0);
    assertEquals(-459.67, t.getFahrenheit(), DELTA);
  }
  
  @Test
  public void testSwapKelvinF1() {
    try {
      Temperature t = new Temperature();
      double k = 0.0;
      t.setByKelvin(k);
      double f = t.getFahrenheit();
      t.setByFahrenheit(f);
      assertEquals(k, t.getKelvin(), DELTA);    
    } catch (TemperatureException e) {
      //Not expected
    }
  }
  
  @Test
  public void testSwapKelvinF2() {
    try {
      Temperature t = new Temperature();
      double k = 20.0;
      t.setByKelvin(k);
      double f = t.getFahrenheit();
      t.setByFahrenheit(f);
      assertEquals(k, t.getKelvin(), DELTA);    
    } catch (TemperatureException e) {
      //Not expected
    }
  }
  
  @Test
  public void testSwapKelvinF3() {
    try {
      Temperature t = new Temperature();
      double k = 50.0;
      t.setByKelvin(k);
      double f = t.getFahrenheit();
      t.setByFahrenheit(f);
      assertEquals(k, t.getKelvin(), DELTA);    
    } catch (TemperatureException e) {
      //Not expected
    }
  }
  
  @Test
  public void testSwapCelsiusF1() {
    try {
      Temperature t1 = new Temperature();
      double c = 0.0;
      t1.setByCelsius(c);
      Temperature t2 = new Temperature();
      t2.setByFahrenheit(t1.getFahrenheit());
      assertEquals(t2.getCelsius(), c, DELTA);
    } catch (TemperatureException e) {
      //Not Expected
    }
  }
  
  @Test
  public void testSwapCelsiusF2() {
    try {
      Temperature t1 = new Temperature();
      double c = -273.15;
      t1.setByCelsius(c);
      Temperature t2 = new Temperature();
      t2.setByFahrenheit(t1.getFahrenheit());
      assertEquals(t2.getCelsius(), c, DELTA);
    } catch (TemperatureException e) {
      //Not Expected
    }
  }
  
  @Test
  public void testSwapCelsiusF3() {
    try {
      Temperature t1 = new Temperature();
      double c = 20.0;
      t1.setByCelsius(c);
      Temperature t2 = new Temperature();
      t2.setByFahrenheit(t1.getFahrenheit());
      assertEquals(t2.getCelsius(), c, DELTA);
    } catch (TemperatureException e) {
      //Not Expected
    }
  }
}
