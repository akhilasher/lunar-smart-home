# format all files in the arduino directory recursively using clang-format

for file in arduino/**/**/*.ino arduino/**/**/**/*.ino arduino/**/**/**/*.ino; do
  echo "Formatting $file"
  clang-format -i "$file"
done

git add arduino
git commit -m "format code"
git push