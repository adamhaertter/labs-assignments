package labZero;

public class Temperature {

  private double k;

  public Temperature() {
    k = -1;
  }

  public double getKelvin() {
    check(k);
    return k;
  }

  public double getFahrenheit() {
    check(k);
    return (9.0 / 5.0) * k - 459.67;
  }

  public double getCelsius() {
    check(k);
    return k - 273.15;
  }

  public void setByKelvin(double k) {
    this.k = k;
    check(k);
  }

  public void setByFahrenheit(double f) {
    k = (5.0 / 9.0) * (f + 459.67);
    check(k);
  }

  public void setByCelsius(double c) {
    k = c + 273.15;
    check(k);
  }

  private void check(double k) {
    if (k < 0) {
      throw new TemperatureException();
    }
  }

}
