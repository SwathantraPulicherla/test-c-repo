#!/bin/bash

# AI Test Generation Workflow Setup Script
# This script sets up the AI-powered test generation workflow in any C repository

set -e

echo "🤖 AI Test Generation Workflow Setup"
echo "===================================="

# Check if we're in a git repository
if ! git rev-parse --git-dir > /dev/null 2>&1; then
    echo "❌ Error: Not in a git repository"
    exit 1
fi

# Create GitHub workflows directory
echo "📁 Creating .github/workflows directory..."
mkdir -p .github/workflows

# Download the workflow file
echo "⬇️ Downloading AI test generation workflow..."
curl -s https://raw.githubusercontent.com/SwathantraPulicherla/ai-test-gemini-CLI/main/.github/workflows/ai-test-generation.yml -o .github/workflows/ai-test-generation.yml

# Download setup documentation
echo "⬇️ Downloading setup documentation..."
curl -s https://raw.githubusercontent.com/SwathantraPulicherla/ai-test-gemini-CLI/main/AI_TEST_SETUP.md -o AI_TEST_SETUP.md

# Create initial test directory structure
echo "📁 Creating test directory structure..."
mkdir -p tests/generated

# Check for C files
C_FILES=$(find . -name "*.c" -not -path "./tests/*" -not -path "./build/*" -not -path "./cmake-build/*" | wc -l)
if [ "$C_FILES" -eq 0 ]; then
    echo "⚠️ Warning: No C source files found outside test directories"
    echo "   Make sure your .c files are in the repository root or src/ directory"
fi

echo ""
echo "✅ Setup complete!"
echo ""
echo "📋 Next steps:"
echo "1. Go to repository Settings → Secrets and variables → Actions"
echo "2. Add a new repository secret named GEMINI_API_KEY with your Google Gemini API key"
echo "3. Push this workflow to trigger automatic test generation"
echo "4. Or create an issue with the 'ai-test-generate' label"
echo ""
echo "📖 See AI_TEST_SETUP.md for detailed instructions"
echo ""
echo "🔗 Workflow will run on:"
echo "   - Push to main/develop/feature branches"
echo "   - Issues labeled with 'ai-test-generate'"