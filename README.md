# unit-converter
### Description
C++ library for unit conversion.

### Example
```
auto c = unit_converter::Converter("°C", "°F");
std::cout << c.convert(10) << std::endl; /// 10 °C -> 50 °F
std::cout << c.convert(10, true) << std::endl; ///  10 °F -> -12.2222 °C
```

```
auto c = unit_converter::Converter("km/h", "m/s");
std::cout << c.convert(10) << std::endl; /// 10 km/h -> 2.77778 m/s 
std::cout << c.convert(10, true) << std::endl; /// 10 m/s -> 36 km/h
```

```
auto c = unit_converter::Converter("km/h^2", "m/s^2");
std::cout << c.convert(10) << std::endl; ///   10 km/h^2 -> 0.000771605 m/s^2 
std::cout << c.convert(10, true) << std::endl; /// 10 m/s^2 -> 129600 km/h^2 
```
