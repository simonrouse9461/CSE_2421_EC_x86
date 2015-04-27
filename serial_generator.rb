#!/usr/bin/ruby

# Initialize validation keys
s1_key = 0xbeef
s2_key = factorize(0xc0ffee)[0]
s3_key = factorize(0xc0ffee)[1]
s4_key = 0x8086

# Prompt for name
puts '-- Serial Number Generator --'
puts 'Enter your name (First Last):'
name = gets

# Compute the sum of ASCII code of all char in name
name_code = sum name

# Calculate each part of the serial number
# This part is just the implementation of the pseudo solution described in disassembly.c
serial_1 = to_hex_code(extend_word(s1_key) + name_code)
serial_2 = to_hex_code(extend_word(s2_key) + name_code)
serial_3 = to_hex_code(extend_word(s3_key) - name_code)
serial_4 = to_hex_code(((extend_word(s4_key) - name_code ^ s4_key) + s4_key ^ s4_key) - s4_key)

# Print serial number
puts "\nHere's your product's serial number:"
puts [serial_1, serial_2, serial_3, serial_4].join '-'
puts "\nKey successfully generated!"

# Function definition section
BEGIN {
  # Get closest factor pair
  def factorize(number)
    # Get rounded square root of the number
    i = (Math.sqrt number).to_int
    # Keep subtracting one from that square root until it divides the original number
    i -= 1 until number % i == 0
    # Return the found factor and the corresponding factor
    [i, number / i]
  end

  # Get sum of ASCII code
  def sum(name)
    # Get rid of new line character and convert to lowercase
    name.chomp!.downcase!
    # Loop through each byte and get the sum
    result = 0
    name.each_byte do |c|
      result += c
    end
    result
  end

  # Extend word to dword
  def extend_word(hex)
    # Pad with f
    hex + 0xffff0000
  end

  # Convert to hex format and get lowest two bytes
  def to_hex_code(num)
    num.to_s(16)[-4, 4]
  end
}
