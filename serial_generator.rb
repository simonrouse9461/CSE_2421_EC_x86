#!/usr/bin/ruby

# validation keys
s1_key = 0xbeef
s2_key = factorize(0xc0ffee)[0]
s3_key = factorize(0xc0ffee)[1]
s4_key = 0x8086

puts '-- Serial Number Generator --'
puts 'Enter your name (First Last):'
name = gets # Read in name
name_code = sum name # Get sum of ASCII code of all char in name

# Calculate each part of the serial number
serial_1 = to_hex_code(extend_word(s1_key) + name_code)
serial_2 = to_hex_code(extend_word(s2_key) + name_code)
serial_3 = to_hex_code(extend_word(s3_key) - name_code)
serial_4 = to_hex_code(((extend_word(s4_key) - name_code ^ s4_key) + s4_key ^ s4_key) - s4_key)

# Print serial number
puts "\nHere's your product's serial number:"
puts [serial_1, serial_2, serial_3, serial_4].join '-'
puts "\nKey successfully generated!"

BEGIN {
  # Get closest factor pair
  def factorize(number)
    i = (Math.sqrt number).to_int
    i -= 1 until number % i == 0
    [i, number / i]
  end

  # Get sum of ASCII code
  def sum(name)
    name.chomp!.downcase!
    result = 0
    name.each_byte do |c|
      result += c
    end
    result
  end

  # Extend word to dword
  def extend_word(hex)
    hex + 0xffff0000
  end

  # Convert to hex format and get lowest two bytes
  def to_hex_code(num)
    num.to_s(16)[-4, 4]
  end
}