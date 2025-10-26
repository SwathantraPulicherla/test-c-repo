# AI-Powered C Test Generation CI/CD

This repository demonstrates automated C unit testing with AI-generated test cases and coverage reporting.

## 🚀 CI/CD Pipeline

The GitHub Actions workflow automatically runs when:
- **Push** to `main` or `test` branches
- **Pull Request** targeting `main` or `test` branches
- **Issue Created/Reopened** (triggers AI test generation)

The workflow:
1. **Clones** the universal-c-testgen tool
2. **Generates Tests**: Uses Google Gemini AI to create comprehensive unit tests
3. **Builds**: Compiles tests with coverage instrumentation using CMake
4. **Runs Tests**: Executes all generated test suites
5. **Coverage Reports**: Generates HTML coverage reports with LCOV
6. **Summary**: Creates detailed workflow summary with coverage report links

## 📊 Coverage Reports & Summary

On successful runs, the workflow provides:

### 📈 **HTML Coverage Report**
- **Location**: Actions artifacts (`coverage-report` folder)
- **Content**: Interactive coverage visualization with line-by-line details
- **Access**: Download from Actions → Workflow run → Artifacts

### 📋 **Workflow Summary**
The workflow automatically creates a detailed summary visible in:
- **Actions** tab → Workflow run → **Summary** section
- Shows test results, coverage links, and key features
- Includes direct links to download coverage reports

### 📦 **Artifacts**
- `coverage-report/` - HTML coverage visualization
- `test-executables/` - Compiled binaries and coverage data

## 🔧 Setup for Your Project

### 1. Add GitHub Secrets
```
Settings → Secrets and variables → Actions → New repository secret
Name: GEMINI_API_KEY
Value: your_google_gemini_api_key
```
**Note**: The workflow uses `GOOGLE_API_KEY` environment variable internally, but you should name the secret `GEMINI_API_KEY` for clarity.

### 2. Project Structure
```
your-c-project/
├── .github/workflows/ci.yml    # This workflow
├── CMakeLists.txt              # Build configuration
├── src/                        # Your C source files
├── tests/generated/            # AI-generated tests (created automatically)
└── unity/                      # Unity testing framework
```

### 3. Workflow Configuration
The workflow runs on:
- **Push** to `main` or `test` branches
- **Pull Requests** targeting `main` or `test` branches

### 4. Using with Universal C TestGen

For full AI-powered testing, integrate with the [universal-c-testgen](https://github.com/SwathantraPulicherla/universal-c-testgen) tool:

```yaml
- name: Clone test generator
  run: git clone https://github.com/SwathantraPulicherla/universal-c-testgen.git

- name: Generate and run tests
  run: python universal-c-testgen/src/scripts/run_testgen.py . --build --run --coverage
  env:
    GEMINI_API_KEY: ${{ secrets.GEMINI_API_KEY }}
```

## 📈 Coverage Report Access

After workflow completion:
1. Go to **Actions** tab
2. Click on the latest workflow run
3. Download **coverage-report** artifact
4. Open `index.html` in your browser

## 🎯 Triggers

The workflow runs automatically on:
- **Push** to `main` or `test` branches
- **Pull Requests** targeting `main` or `test` branches
- **Issue Creation/Reopening** - Creates an issue to trigger AI test generation

### 💡 Issue-Triggered Testing

To manually trigger AI test generation:
1. Go to **Issues** tab
2. Click **New Issue**
3. The workflow will automatically run and generate tests
4. View results in the Actions tab and issue comments

## 🔍 Troubleshooting

- **Missing API Key**: Add `GEMINI_API_KEY` to repository secrets
- **Build Failures**: Check CMake configuration and dependencies
- **Coverage Issues**: Ensure LCOV is installed (Ubuntu runners have it by default)

---

**Note**: This demo uses pre-generated tests. For full AI-powered testing, integrate with the universal-c-testgen tool.