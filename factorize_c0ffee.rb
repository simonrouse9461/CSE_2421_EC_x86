#!/usr/bin/ruby

i = (Math.sqrt 0xc0ffee).to_int
i -= 1 until 0xc0ffee % i == 0
puts i.to_s(16)
puts (0xc0ffee / i).to_s(16)
