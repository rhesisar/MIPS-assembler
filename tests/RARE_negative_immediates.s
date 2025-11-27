ADDI $11,$10,-3 # 16 bits
ADDI $2,$0,20
LW $4,-4($2) # 16 bits
SLL $4,$5,4
BGTZ $23,-4 # 16 bits
ROTR $9,$8,3 # 5 bits
ROTR $9,$8,-3 # 5 bits
SLL $9,$8,3 # 5 bits
SLL $9,$8,-3 # 5 bits

# EXPECTED_ASSEMBLY
# 214bfffd
# 20020014
# 8c44fffc
# 00052100
# 1ee0fffc
# 002848c2
# 00284f42
# 000848c0
# 00084f40

# EXPECTED_FINAL_STATE
# $02:20
# $11:-3
