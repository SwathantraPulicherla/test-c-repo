# AI Test Generation Workflow Setup

This repository includes automated AI-powered unit test generation using GitHub Actions.

## Setup Instructions

### 1. Add Gemini API Key Secret

1. Go to your repository settings
2. Navigate to "Secrets and variables" → "Actions"
3. Click "New repository secret"
4. Name: `GEMINI_API_KEY`
5. Value: Your Google Gemini API key

### 2. Trigger Test Generation

The workflow runs automatically on:

- **Push events** to `main`, `develop`, or any `feature/**` branch
- **Issue creation** with the `ai-test-generate` label

### 3. Manual Trigger via Issues

1. Create a new issue in your repository
2. Add the label `ai-test-generate`
3. The workflow will automatically generate tests and comment on the issue

## What Gets Generated

- **Test Files**: `tests/generated/test_*.c` for each source file
- **Unity Framework**: Minimal Unity testing framework in `unity/src/`
- **Validation Reports**: Quality assessment of generated tests
- **Compilation Checks**: Automatic compilation verification

## Workflow Features

- **Smart Filtering**: Only generates tests for source files, excludes existing tests
- **Dependency Analysis**: Automatically creates stubs for external dependencies
- **Quality Validation**: Comprehensive checks for compilation safety and test quality
- **Auto-commit**: Generated tests are automatically committed back to the repository

## Repository Structure After Generation

```
your-repo/
├── .github/workflows/
│   └── ai-test-generation.yml
├── src/
│   ├── your_code.c
│   └── your_code.h
├── tests/
│   └── generated/
│       ├── test_your_code.c
│       └── ...
├── unity/
│   └── src/
│       ├── unity.h
│       └── unity.c
└── README.md
```

## Local Testing

To test the workflow locally before pushing:

```bash
# Clone the test generator
git clone https://github.com/SwathantraPulicherla/ai-test-gemini-CLI.git testgen-tool

# Run test generation
python testgen-tool/src/scripts/run_testgen.py . --api-key YOUR_API_KEY

# Validate tests
python testgen-tool/src/scripts/run_testgen.py . --api-key YOUR_API_KEY | grep -E "(✅|❌|⚠️)"
```

## Troubleshooting

### Common Issues

1. **Missing API Key**: Ensure `GEMINI_API_KEY` secret is set in repository settings
2. **Compilation Errors**: Check that all required headers exist in the repository
3. **No Tests Generated**: Verify that `.c` files exist in the repository and aren't in excluded directories

### Workflow Logs

Check the "Actions" tab in your repository for detailed workflow logs and error messages.