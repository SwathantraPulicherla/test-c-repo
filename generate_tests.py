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
    test_code = response.text
    if test_code is None:
        test_code = "// No response from AI"
    else:
        test_code = test_code.strip()
        
        # Remove markdown code blocks if present
        if test_code.startswith('```c'):
            test_code = test_code[4:]
        if test_code.startswith('```'):
            test_code = test_code[3:]
        if test_code.endswith('```'):
            test_code = test_code[:-3]
        test_code = test_code.strip()
    
    return test_code

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
