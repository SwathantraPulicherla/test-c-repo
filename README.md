# Universal C Test Generator Setup

This repository uses an AI-powered test generator for C code using the Unity testing framework.

## Setup for New Repositories

To use this in any C repository:

1. **Add the workflow**: Copy `.github/workflows/test.yml` to your repository.

2. **Set up Google Gemini API**:
   - Go to [Google AI Studio](https://aistudio.google.com/) and get an API key.
   - In your GitHub repository, go to Settings > Secrets and variables > Actions.
   - Add a new repository secret named `GOOGLE_API_KEY` with your API key.

3. **Repository Structure**:
   - Place your C source files in `src/` (e.g., `src/my_module.c`, `src/my_module.h`).
   - Ensure your code has header files for the functions you want to test.

4. **Push your code**: On push or PR, the workflow will:
   - Set up the Unity framework and test generator.
   - Generate tests for all `.c` files in `src/`.
   - Build and run the tests.

## Local Development

For local testing:

1. Run `./setup_testgen.sh` to add the necessary files.
2. Set `export GOOGLE_API_KEY=your_key`.
3. Generate tests: `python generate_tests.py src/your_file.c`.
4. Run tests: `make test`.

## Notes

- Tests are generated in `tests/generated/` and not committed to the repository.
- The tool uses Gemini AI to analyze your code and create comprehensive test cases.
- Requires C source files with corresponding headers.