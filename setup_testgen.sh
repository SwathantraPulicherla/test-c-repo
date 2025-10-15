#!/bin/bash

# Script to set up the universal C test generator tool in a developer's repository.
# This adds the necessary extra files (Unity framework, generate_tests.py, Makefile)
# without modifying the original tool repository.

set -e  # Exit on any error

TOOL_REPO="https://github.com/SwathantraPulicherla/Gemini-Agent-and-api.git"
TEMP_DIR="temp_tool_setup"

echo "Setting up universal C test generator..."

# Clone the tool repository temporarily
echo "Cloning tool repository..."
git clone --depth 1 "$TOOL_REPO" "$TEMP_DIR"

# Copy the required files
echo "Copying Unity framework..."
cp -r "$TEMP_DIR/unity" .

echo "Copying Makefile..."
cp "$TEMP_DIR/Makefile" .

echo "Creating test generation script..."
cat > generate_tests.py << 'EOF'
import google.generativeai as genai
import os
import sys

# Configure API key - set GOOGLE_API_KEY environment variable
genai.configure(api_key=os.getenv('GOOGLE_API_KEY'))

model = genai.GenerativeModel('models/gemini-2.5-flash')

def generate_test(c_code):
    prompt = f"""Generate comprehensive unit tests for the following C code using the Unity testing framework.

Requirements:
- Include setUp and tearDown functions if needed
- Generate test functions for each public function in the code
- Use appropriate Unity assertions (TEST_ASSERT_EQUAL, TEST_ASSERT_TRUE, etc.)
- Test edge cases, normal cases, and error cases
- Follow Unity conventions

C Code:
{c_code}

Generate only the test function implementations, without main or includes."""

    response = model.generate_content(prompt)
    return response.text

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python generate_tests.py <c_file>")
        sys.exit(1)

    c_file = sys.argv[1]
    with open(c_file, 'r') as f:
        c_code = f.read()

    test_code = generate_test(c_code)

    # Create test file
    base_name = os.path.basename(c_file).replace('.c', '')
    os.makedirs("tests/generated", exist_ok=True)
    test_file = f"tests/generated/test_{base_name}.c"

    with open(test_file, 'w') as f:
        f.write('#include "unity.h"\n')
        f.write(f'#include "{base_name}.h"\n\n')
        f.write('void setUp(void) {}\n')
        f.write('void tearDown(void) {}\n\n')
        f.write(test_code)

    print(f"Test generated in {test_file}")

    # Also create a test_main.c if it doesn't exist
    main_file = "tests/generated/test_main.c"
    if not os.path.exists(main_file):
        with open(main_file, 'w') as f:
            f.write('#include "unity.h"\n\n')
            f.write('// Test prototypes will be added here\n\n')
            f.write('int main(void) {\n')
            f.write('    UNITY_BEGIN();\n')
            f.write('    // RUN_TEST calls will be added here\n')
            f.write('    return UNITY_END();\n')
            f.write('}\n')
EOF

# Clean up
echo "Cleaning up..."
rm -rf "$TEMP_DIR"

echo "Setup complete!"
echo ""
echo "To use the test generator:"
echo "1. Ensure GOOGLE_API_KEY environment variable is set"
echo "2. Run: python generate_tests.py src/your_source_file.c"
echo "3. Build and run tests: make test"
echo ""
echo "Note: Generated tests will be placed in tests/generated/"