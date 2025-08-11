#!/bin/bash
# OrangeOS QEMU Launch Script

# Check if OS image exists
if [ ! -f "orangeos.img" ]; then
    echo "OS image not found. Building..."
    make
fi

# Check if build was successful
if [ ! -f "orangeos.img" ]; then
    echo "Build failed. Cannot run OS."
    exit 1
fi

echo "Starting OrangeOS in QEMU..."
echo "Press Ctrl+Alt+G to release mouse cursor"
echo "Press Ctrl+Alt+2 to access QEMU monitor"
echo "Press Ctrl+Alt+1 to return to OS"
echo ""

# Run QEMU with appropriate settings
qemu-system-i386 \
    -fda orangeos.img \
    -boot a \
    -m 16M \
    -rtc base=localtime \
    -name "OrangeOS Educational OS" \
    -display gtk