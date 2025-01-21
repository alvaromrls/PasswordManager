#include "gtest/gtest.h"
#include "PasswordGenerator.h"
#include "PasswordBuilder.h"

// Test básico de inicialización
TEST(PasswordGeneratorBuilderTest, DefaultInitialization)
{
    PasswordGeneratorBuilder<PasswordGenerator> builder;
    auto generator = builder.build();
    EXPECT_NE(generator, nullptr);
}

// Test de configuración progresiva
TEST(PasswordGeneratorBuilderTest, ConfigureBuilder)
{
    PasswordGeneratorBuilder<PasswordGenerator> builder;
    auto generator = builder.setLength(12)
                         .includeUppercase(true)
                         .includeSpecialChars(true)
                         .includeNumbers(true)
                         .build();
    EXPECT_NE(generator, nullptr);
}

class MockPasswordGenerator : public PasswordGenerator
{
public:
    MockPasswordGenerator(int length, bool includeUppercase, bool includeSpecialChars, bool includeNumbers)
        : PasswordGenerator(length, includeUppercase, includeSpecialChars, includeNumbers),
          mockLength(length), mockIncludeUppercase(includeUppercase),
          mockIncludeSpecialChars(includeSpecialChars), mockIncludeNumbers(includeNumbers) {}

    // Métodos de acceso para verificar configuraciones
    int getLength() const { return mockLength; }
    bool includesUppercase() const { return mockIncludeUppercase; }
    bool includesSpecialChars() const { return mockIncludeSpecialChars; }
    bool includesNumbers() const { return mockIncludeNumbers; }

private:
    int mockLength;
    bool mockIncludeUppercase;
    bool mockIncludeSpecialChars;
    bool mockIncludeNumbers;
};

// Test con el mock: configuraciones transferidas correctamente
TEST(PasswordGeneratorBuilderTest, MockPasswordGenerator)
{
    PasswordGeneratorBuilder<MockPasswordGenerator> builder;
    auto mockGenerator = builder.setLength(15)
                             .includeUppercase(true)
                             .includeSpecialChars(false)
                             .includeNumbers(true)
                             .build();

    EXPECT_EQ(mockGenerator->getLength(), 15);
    EXPECT_TRUE(mockGenerator->includesUppercase());
    EXPECT_FALSE(mockGenerator->includesSpecialChars());
    EXPECT_TRUE(mockGenerator->includesNumbers());
}

// Test de excepción por longitud inválida
TEST(PasswordGeneratorBuilderTest, InvalidLengthThrows)
{
    PasswordGeneratorBuilder<PasswordGenerator> builder;
    EXPECT_THROW(builder.setLength(4).build(), std::invalid_argument);
}
