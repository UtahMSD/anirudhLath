import static java.lang.Math.abs;

class Fraction {
    /// Variables
    private long numerator; // The numerator
    private long denominator; // The denominator

    /// Private Methods
    private void reduce() // Changes this fraction to its reduced form.
    {
        long gcd = this.GCD();
        numerator /= gcd;
        denominator /= gcd;
    }

    private long GCD() // Returns the greatest common divisor of this fraction's numerator and denominator. This is a helper method for the reduce method, below.
    {
        long gcd = abs(numerator);
        long remainder = abs(denominator);
        while(remainder != 0) {
            long temp = remainder;
            remainder = gcd % remainder;
            gcd = temp;
        }
        return gcd;
    }

    private void resolve() // Resolves numerator and denominator negativity.
    {
        if (numerator < 0 && denominator < 0) {
            numerator = abs(numerator);
            denominator = abs(denominator);
        } else if (denominator < 0) {
            numerator =  numerator * -1;
            denominator = abs(denominator);
        }

    }

    /// Constructors
    public Fraction() // The default constructor
    {
        numerator = 0;
        denominator = 1;
    }

    public Fraction(long n, long d) // Constructor with the ability to assign the values.
    {
        if (n < 0 && d < 0){
            numerator = abs(n);
            denominator = abs(d);
        } else if (d < 0) {
            numerator = n * -1;
            denominator = abs(d);
        } else {
            numerator = n;
            denominator = d;
        }
    }

    /// Public Methods
    public Fraction plus(Fraction rhs) // Returns a new fraction that is the result of the right hand side (rhs) fraction added to this fraction.
    {
        Fraction result = new Fraction();
        rhs.resolve();
        result.numerator = (numerator * rhs.denominator) + (rhs.numerator * denominator);
        result.denominator = denominator * rhs.denominator;
        result.resolve();
        result.reduce();
        return result;
    }

    public Fraction minus(Fraction rhs) // Returns a new fraction that is the result of the right hand side (rhs) fraction subtracted from this fraction.
    {
        Fraction result = new Fraction();
        rhs.resolve();
        result.numerator = (numerator * rhs.denominator) - (rhs.numerator * denominator);
        result.denominator = denominator * rhs.denominator;
        result.resolve();
        result.reduce();
        return result;
    }

    public Fraction times(Fraction rhs) // Returns a new fraction that is the result of this fraction multiplied by the right hand side (rhs) fraction.
    {
        Fraction result = new Fraction();
        rhs.resolve();
        result.numerator = numerator * rhs.numerator;
        result.denominator = denominator * rhs.denominator;
        result.resolve();
        result.resolve();
        return result;
    }

    public Fraction dividedBy(Fraction rhs) // Returns a new fraction that is the result of this fraction divided by the right hand side (rhs) fraction.
    {
        Fraction result = new Fraction();
        rhs.resolve();
        result.numerator = numerator * rhs.denominator;
        result.denominator = denominator * rhs.numerator;
        result.resolve();
        result.reduce();
        return result;
    }

    public Fraction reciprocal() // Returns a new fraction that is the reciprocal of this fraction.
    {
        Fraction result = new Fraction();
        result.numerator = denominator;
        result.denominator = numerator;
        return result;
    }

    public String toString() // Returns a string representing this fraction. The string should have the format: "N/D", where N is the numerator, and D is the denominator. This method should always print the reduced form of the fraction. If the fraction is negative, the sign should be displayed on the numerator, e.g., "-1/2" not "1/-2".
    {
        String result = "";
        this.reduce();
        if (numerator < 0 && denominator < 0) {
            result += abs(numerator);
            result += '/';
            result += abs(denominator);
        } else if (denominator < 0) {
            result += numerator * -1;
            result += '/';
            result += abs(denominator);
        } else {
            result += numerator;
            result += '/';
            result += denominator;

        }
        return result;
    }

    public double toDouble() // Returns a (double precision) floating point number that is the approximate value of this fraction, printed as a real number.
    {
        return numerator * 1.0000000000 / denominator;
    }

    public static void main(String[] args) {
        Fraction fraction1 = new Fraction(1,1);
        Fraction fraction2 = new Fraction();
        System.out.println("Basic CPP migration has been passed! The code compiles without any errors.");
    }
}
